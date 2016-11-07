import sys
import ROOT as rt
import math
from LHEevent import *
from LHEfile import *
import plotTools

if __name__ == '__main__':

    #Bprime histograms
    MBPrime = rt.TH1D("MBPrime", "MBPrime", 200, 100.0, 200.0)
    MX = rt.TH1D("MX", "MX", 500, 0., 50)
    Mb = rt.TH1F("Mb", "Mb", 30, 2.0, 8.0)
    MInvariantMass = rt.TH1F("MInvariantMass", "MInvariantMass", 500, 0., 50);    
    mu1_lv = rt.TLorentzVector()
    mu2_lv = rt.TLorentzVector()

    # find events in file
    myLHEfile = LHEfile(sys.argv[1])
    myLHEfile.setMax(100000)
    eventsReadIn = myLHEfile.readEvents()
    for oneEvent in eventsReadIn:
        sum_mu = 0
        myLHEevent = LHEevent()
        myLHEevent.fillEvent(oneEvent)
        for i in range(0,len(myLHEevent.Particles)):
            p = myLHEevent.Particles[i]
            if abs(p['ID']) == 13:
              sum_mu += 1
            if sum_mu==1: 
              mu1_lv = rt.TLorentzVector(p['Px'], p['Py'], p['Pz'], p['E'])
            elif sum_mu==2:
              mu2_lv = rt.TLorentzVector(p['Px'], p['Py'], p['Pz'], p['E'])
            MInvariantMass.Fill((mu1_lv+mu2_lv).M());
            if abs(p['ID']) == 8000002: MBPrime.Fill(p['M'])
            if (abs(p['ID']) ==5 and p['M'] > 0.0): Mb.Fill(p['M'])
            if abs(p['ID']) == 23: MX.Fill(p['M'])
        del oneEvent, myLHEevent
        
    # write the histograms
    histoFILE = rt.TFile(sys.argv[2],"RECREATE")
    MBPrime.Write()
    MX.Write()
    Mb.Write()
    MInvariantMass.Write();
    histoFILE.Close()
