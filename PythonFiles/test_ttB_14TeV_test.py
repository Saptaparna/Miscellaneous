from ROOT import *
from glob import glob

gROOT.SetStyle("Plain")
gStyle.SetTitleX(0.5)
gStyle.SetTitleAlign(23)


bins=["/eos/cms/store/group/phys_higgs/upgrade/PhaseII/Configuration4v2/140PileUp/ttB-4p-0-900-v1510_14TEV",
      "/eos/cms/store/group/phys_higgs/upgrade/PhaseII/Configuration4v2/140PileUp/ttB-4p-900-1600-v1510_14TEV",
      "/eos/cms/store/group/phys_higgs/upgrade/PhaseII/Configuration4v2/140PileUp/ttB-4p-1600-2500-v1510_14TEV",
      "/eos/cms/store/group/phys_higgs/upgrade/PhaseII/Configuration4v2/140PileUp/ttB-4p-2500-100000-v1510_14TEV"]

sigmas=[2.6673,
        0.250469,
        0.0237441,
        0.00208816]

canv=TCanvas()
canv.SetLogy()

hist=TH1F("h","h",500,0,20000)
stack=THStack()
histograms=[]
dumb=[]
chains=[]
legend=TLegend(0.5,0.5,0.8,0.8)
histnames = ['0-900', '900-1600', '1600-2500', '2500-100000']
for bin, sigma, hist in zip(bins, sigmas, histnames):
    #print bin
    #f=TFile(file)
    #t=f.Get("Delphes")

    c=TChain("Delphes")
    #files=open('filename.txt')
    #file=files.readline()
    #print file 
    #files=glob(bin+'/*root')
    #files = "root://eoscms//eos/cms/store/group/phys_higgs/upgrade/PhaseII/Configuration4v2/140PileUp/ttB-4p-0-900-v1510_14TEV/ttB-4p-0-900-v1510_14TEV_97512976_PhaseII_Conf4v2_140PileUp.root"
    for file in open('filename.txt').xreadlines():    
        print file 
        c.Add(file)
        #file1=file  
        #c.Add("root://eoscms.cern.ch/"+file.replace('/eos/cms/store','/eos/cms/store'))
    #c.Add("root://eoscms//eos/cms/store/group/phys_higgs/upgrade/PhaseII/Configuration4v2/140PileUp/ttB-4p-0-900-v1510_14TEV/ttB-4p-0-900-v1510_14TEV_97512976_PhaseII_Conf4v2_140PileUp.root")
    #c.Add(file1)
    hname="h"+str(len(histograms))
    c.Draw("HT>>"+hname+"(500,0,3000)","Event.Weight")
    h=gPad.GetPrimitive(hname)
    h.Scale(sigma/h.Integral(0,h.GetNbinsX()+1))
    h.SetFillColor(1+len(histograms))
    h.SetStats(kFALSE)
    stack.Add(h)
    histograms.append(h)
    legend.SetFillColor(0)
    legend.SetHeader("H_{T} bins at 14 TeV")
    legend.AddEntry(h, hist, "f")
    #dumb.append(f)

stack.SetTitle("T#bar{T}V sample summed over H_{T} bins; H_{T} [GeV]")
stack.Draw()
stack.SetMinimum(.0001)
stack.Draw()
legend.Draw()
c1.SaveAs("ttB_summed_14TeV.C")
c1.SaveAs("ttB_summed_14TeV.pdf")
c1.SaveAs("ttB_summed_14TeV.png")
