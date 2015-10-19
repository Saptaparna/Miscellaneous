import ROOT

#load library with dictionaries for objects in tree                                                                                                                                                                
ROOT.gSystem.Load("libFWCoreFWLite.so")
ROOT.AutoLibraryLoader.enable()

#open ROOT file                                                                                                                                                                                                    
fIn=ROOT.TFile.Open('test/Output_HGCanalysis.root')

#prepare some control histograms                                                                                                                                                                                
recHitTimeH = ROOT.TH1F('rechittime',';RecHit time [ns];Regions of interest',100,-0.2,0.2)
collTimeH = ROOT.TH1F('colltime',';Collision time [ns];Regions of interest',100,-0.2,0.2)

#read tree from file                                                                                                                                                                                               
tree=fIn.Get('analysis/HGC')
print 'Preparing to analyse %d events'%tree.GetEntriesFast()

#loop over events in tree                                                                                                                                                                                          
#for i in xrange(0,1) :
for i in xrange(0,tree.GetEntriesFast()) :

    tree.GetEntry(i)

    #print event summary                                                                                                                                                                                           
    #print '-'*50
    #print '(run,event,lumi)=',tree.run,tree.event,tree.lumi
    #print '(vx,vy,vz)=',tree.GenVertex.X(),tree.GenVertex.Y(),tree.GenVertex.Z()
    #print '%d reconstructed vertices' % tree.Vertices.size()
    #print '%d rec hits, in %d clusters, in %d ROIs' % (tree.RecHits.size(),tree.Clusters.size(),tree.ROIs.size())

        # loop over the hits                                                                                                                                                                                        
    roiInfo={}
    for hit in tree.RecHits:

        #select hits with time                                                                                                                                                                                 
        if hit.t_<0 : continue

        #get the region of interest                                                                                                                                                                             
        roiId= tree.Clusters[ hit.clustId_ ].roiidx_
        #clusterTime = tree.Clusters[hit.clustId_].sigma_1_
        #clusterSize = hit.cellSize_
        #print clusterTime
        #print clusterSize
        #init hit, energy and timing counters                                                                                                                                                                   
        if not roiId in roiInfo : roiInfo[roiId]=[0.,0.,0.,0.]
        roiInfo[roiId][0] += 1
        roiInfo[roiId][1] += hit.en_
        roiInfo[roiId][2] += hit.t_
        roiInfo[roiId][3] += hit.t_*hit.en_

    #now finish the averages and print information on ROI                                                                                                                                                       
    for roiId in roiInfo:

        #id of the matched particle                                                                                                                                                                             
        particleMatchId=tree.ROIs[roiId].stableid_

        #place of interaction of the matched particle (if>317 cm then it happened inHGC)                                                                                                                        
        zinter=ROOT.TMath.Abs(tree.ROIs[roiId].stablez_)
        if zinter<317 : continue

        #at least one hit found must be required                                                                                                                                                                
        if roiInfo[roiId][0]==0 : continue

        #finish averages                                                                                                                                                                                        
        avgT           = roiInfo[roiId][2]/roiInfo[roiId][0]
        avgT_weightedE = roiInfo[roiId][3]/roiInfo[roiId][1]

        #print information                                                                                                                                                                                      
        #print 'ROI #%d matched to %d (z_{inter}=%fcm) avgT=%fns avgT_weightedE=%fns' %(roiId,particleMatchId,zinter,avgT,avgT_weightedE)

        d=tree.GenVertex.z()          #true vertex position                                                                                                                                                     
        xh,yh,zh=tree.ROIs[roiId].stablex_,tree.ROIs[roiId].stabley_,tree.ROIs[roiId].stablez_   #true interaction in the detector                                                                                                                               
        LIGHTSPEED=29.9792458 #cm/ns                                                                                                                                                                                                                             
        pathDiff = ROOT.TMath.Sqrt(xh**2+yh**2+(zh+d)**2)-ROOT.TMath.Sqrt(xh**2+yh**2+zh**2)
        collTime = avgT+pathDiff/LIGHTSPEED-1.0
        collTimeH.Fill(collTime)
        recHitTimeH.Fill(avgT-1.0)

        #print information                                                                                                                                                                                                                                       
        print '\t average time after correction %fns ' % (collTime)

    

#save histos to file                                                                                                                                                                                            
fOut=ROOT.TFile.Open('SimpleHitAnalysis.root','RECREATE')
collTimeH.Write()
recHitTimeH.Write()
fOut.Close()
