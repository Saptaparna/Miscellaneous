#include "BeamSpotParameters/BeamSpotParameters/interface/BeamSpotParameters.h"

BeamSpotParameters::BeamSpotParameters(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

}


BeamSpotParameters::~BeamSpotParameters()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
BeamSpotParameters::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   edm::Handle<reco::BeamSpot> beamSpotHandle;
   iEvent.getByLabel("offlineBeamSpot", beamSpotHandle);

   //if(not beamSpotHandle.isValid()) continue;

   double x0 = beamSpotHandle->x0();
   std::cout << "x0 = " << x0 << std::endl;
   double y0 = beamSpotHandle->y0();
   std::cout << "y0 = " << y0 << std::endl;
   double z0 = beamSpotHandle->z0();
   std::cout << "z0 = " << z0 << std::endl;
   double sigmaz = beamSpotHandle->sigmaZ();
   std::cout << "sigmaz = " << sigmaz << std::endl;
   double dxdz = beamSpotHandle->dxdz();
   std::cout << "dxdz = " << dxdz << std::endl;
   double BeamWidthX = beamSpotHandle->BeamWidthX();
   std::cout << "BeamWidthX = " << BeamWidthX << std::endl;
   double BeamWidthY = beamSpotHandle->BeamWidthY();
   //std::cout << "BeamWidthY = " << BeamWidthY << std::endl;
   //double BeamWidthZ = beamSpotHandle->BeamWidthZ();
   //std::cout << "BeamWidthZ = " << BeamWidthZ << std::endl;
}


// ------------ method called once each job just before starting event loop  ------------
void 
BeamSpotParameters::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
BeamSpotParameters::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
BeamSpotParameters::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
BeamSpotParameters::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
BeamSpotParameters::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
BeamSpotParameters::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
BeamSpotParameters::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(BeamSpotParameters);
