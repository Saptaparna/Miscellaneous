
#include "BTagTest/BTagSoftLeptonAnalyzer/interface/GluonSplittingToBBFinder.h"

//returns type of event: 1 FCR, 2 FEX, 3 GS, -1 none of those
//int GluonSplittingToBBFinder::procDisc( const reco::GenParticleCollection & gpc, edm::RefToBase<reco::Jet> jet, float deltaR, float m, bool useJet=0)


int GluonSplittingToBBFinder::n_b_from_gluons( const reco::GenParticleCollection & gpc, const reco::Jet jet, float deltaR, float m, bool useJet=0)
{
  int _n_b=0; // 
  int _nb_nojet=0; // number of b quarks that come from gluons
  int _nb_dr_match=0; // ...matched with the jet within deltaR
  int _nb_dr_frac_match=0; // ... and the gluon carries at least "m" fraction of the energy of the jet

  int status = -1;

  for (reco::GenParticleCollection::const_iterator gp=gpc.begin(); gp!=gpc.end(); gp++){
    if( ((useJet==false) && (abs(gp->pdgId())==5 and gp->mother(0)->pdgId()==21))
	||
	((useJet==true ) && (abs(gp->pdgId())==5 and gp->mother(0)->pdgId()==21) && (fabs(matchDR(*gp,jet))<deltaR))
	) _n_b++;

    if (abs(gp->pdgId())==5 and gp->mother(0)->pdgId()==21){
      _nb_nojet++;
      if(fabs(matchDR(*gp,jet))<deltaR){
	_nb_dr_match++;
	if(matchFrac(*(gp->mother(0)),jet,m)){
	  _nb_dr_frac_match++;
	}
      }
    }
  }
  if (_nb_dr_frac_match>1) status=3;
  else if (_nb_dr_match>1) status=2;
  else if (_nb_nojet>1) status=1;
  else if (_n_b>1) status=0;
  else status=-1;
  return status;
}


int GluonSplittingToBBFinder::has_b_quark( const reco::GenParticleCollection & gpc, const reco::Jet jet, float deltaR, float m ){
  int result = -1;

  //std::cout << "GP collection size: " << gpc.size() << std::endl;

   for (reco::GenParticleCollection::const_iterator gp=gpc.begin(); gp!=gpc.end(); gp++){

     int _status = -1;

     while(1){
       if ( (abs(gp->pdgId())==5) ) _status = 1;
       else break;
       if ( (fabs(matchDR(*gp,jet))<deltaR) ) _status = 2;
       else break;
       if ( (matchFrac(*gp, jet, m)) ) _status = 3;
       else break;
       break;
     }
     if (result<_status) result = _status;
   }
   return result;
}




int GluonSplittingToBBFinder::procDisc( const reco::GenParticleCollection & gpc, const reco::Jet jet, float deltaR, float m, bool useJet=0)
{
  int part3=0, anti3=0, part2=0, anti2=0;
  float  maxp3=-1000, maxa3 = -1000, maxa2=-1000, maxp2=-1000;
  const reco::Candidate* mp2=0, *mp3=0, *ma2=0, *ma3=0;

  

  //std::cout <<" JET PX "<<jet.px()<<std::endl;


  for(unsigned int i=0; i<gpc.size(); i++){
    //std::cout <<"   DEBUG: gen particle pdgId = "<<gpc[i].pdgId() << "   status = "<<gpc[i].status() << "   pt = "<<gpc[i].pt() <<std::endl;
    if ((useJet == true &&  std::abs(matchDR( gpc[i],jet))< deltaR)|| (useJet == false) ){
      //std::cout <<" --->DELTA = "<<matchDR( gpc[i],jet)<<std::endl;
      if(gpc[i].pdgId()==5 && gpc[i].status()==3 && gpc[i].pt()>maxp3) {  
	part3++;
	maxp3 = gpc[i].pt();
	mp3 = gpc[i].mother(0);
	//      bvec.push_back(&gpc[i]);
      }
      if(gpc[i].pdgId()==-5 && gpc[i].status()==3 && gpc[i].pt()>maxa3) {
	anti3++;
	maxa3 = gpc[i].pt();
	ma3 = gpc[i].mother(0);
	//      bvec.push_back(&gpc[i]);
      }
      if(gpc[i].pdgId()==5 && gpc[i].status()==2 && gpc[i].pt()>maxp2) {
	part2++;
	maxp2 = gpc[i].pt();
	mp2 = gpc[i].mother(0);
	//	std::cout <<" 5 with mothers "<<gpc[i].numberOfMothers()<<" first is a "<<(gpc[i].mother(0))->pdgId()
	//		  <<" from "<< gpc[i].mother(0)
	//		  <<" mmother Pt "<< gpc[i].mother(0)->pt()
	//		  <<std::endl;
	//      bvec.push_back(&gpc[i]);
      }
      if(gpc[i].pdgId()==-5 && gpc[i].status()==2 && gpc[i].pt()>maxp2) {
	anti2++;
	maxa2 = gpc[i].pt();
	ma2 = gpc[i].mother(0);
	//	std::cout <<" -5 with mothers "<<gpc[i].numberOfMothers()<<" first is a "<<(gpc[i].mother(0))->pdgId()
	//		  <<" from "<< gpc[i].mother(0)
	//		  <<" mmother Pt "<< gpc[i].mother(0)->pt()
	//		  <<std::endl;
	
	//      bvec.push_back(&gpc[i]);
      }
    }
  }	
    if(part3==1 && anti3==1) {
      return 1;
    }
    if((part3>=1&&anti3==0) || (part3==0 && anti3>=1)) 
      {
	return 2; 
      }
    if(part3==0 && anti3==0 && (part2>=1 && anti2>=1) && (ma2==mp2) && (ma2!=0) 
       //&& (ma2->pt()/jet->pt() > m)
       && ((useJet == true && matchFrac(*ma2,jet,m) == true ) || useJet == false)
) { 
      return 3;
    } 
    return -1;
  } 

  

#include <Math/GenVector/Cartesian3D.h>
#include <Math/GenVector/VectorUtil.h>

//double GluonSplittingToBBFinder::matchDR  ( const reco::GenParticle &v1_, edm::RefToBase<reco::Jet> &v2_){
double GluonSplittingToBBFinder::matchDR  ( const reco::GenParticle & v1_, const reco::Jet & v2_){
  using namespace ROOT::Math;
  Cartesian3D<double> v1(v1_.momentum().x(),
			 v1_.momentum().y(),
			 v1_.momentum().z());
  Cartesian3D<double> v2(v2_.px(), v2_.py(), v2_.pz());
  return VectorUtil::DeltaR(v1, v2);
}
//double GluonSplittingToBBFinder::matchFrac  ( const reco::GenParticle &v1_, edm::RefToBase<reco::Jet> &v2_, double frac){
double GluonSplittingToBBFinder::matchFrac  ( const reco::GenParticle &v1_, const reco::Jet & v2_, double frac){
  using namespace ROOT::Math;
  Cartesian3D<double> v1(v1_.momentum().x(),
			 v1_.momentum().y(),
			 v1_.momentum().z());
  Cartesian3D<double> v2(v2_.px(), v2_.py(), v2_.pz());

  return ( ( v1.x()*v1.x() +  v1.y()*v1.y() ) /  ( v2.x()*v2.x() +  v2.y()*v2.y() ) > frac);
}


