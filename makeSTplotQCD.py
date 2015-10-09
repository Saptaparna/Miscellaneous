from ROOT import *
from glob import glob

gROOT.SetStyle("Plain")
gStyle.SetTitleX(0.5)
gStyle.SetTitleAlign(23)

binns=["/eos/cms/store/group/phys_exotica/BH_RunII/MC_Bkg/Ntuples_25ns_21Sep2015/QCD/QCD_HT_100_200_25ns.root",
      "/eos/cms/store/group/phys_exotica/BH_RunII/MC_Bkg/Ntuples_25ns_21Sep2015/QCD/QCD_HT_200_300_25ns.root",
      "/eos/cms/store/group/phys_exotica/BH_RunII/MC_Bkg/Ntuples_25ns_21Sep2015/QCD/QCD_HT_300_500_25ns.root",
      "/eos/cms/store/group/phys_exotica/BH_RunII/MC_Bkg/Ntuples_25ns_21Sep2015/QCD/QCD_HT_500_700_25ns.root",
      "/eos/cms/store/group/phys_exotica/BH_RunII/MC_Bkg/Ntuples_25ns_21Sep2015/QCD/QCD_HT_700_1000_25ns.root",
      "/eos/cms/store/group/phys_exotica/BH_RunII/MC_Bkg/Ntuples_25ns_21Sep2015/QCD/QCD_HT_1000_1500_25ns.root",
      "/eos/cms/store/group/phys_exotica/BH_RunII/MC_Bkg/Ntuples_25ns_21Sep2015/QCD/QCD_HT_1500_2000_25ns.root",
      "/eos/cms/store/group/phys_exotica/BH_RunII/MC_Bkg/Ntuples_25ns_21Sep2015/QCD/QCD_HT_2000_inf_25ns.root"]

sigmas=[27540000.0,
        1735000.0,
        366800.0,
        29370.0,
        6524.0,
        1064.0,
        121.5,
        25.4]

numberOfEvents=[80093092,
	        18717349,
		20086103,
                19542847,
                15011016,
                4963895,
                3848411,
                1961774]

canv=TCanvas()
canv.SetLogy()

hist=TH1F("h","h",500,0,20000)
stack=THStack()
histograms=[]
dumb=[]
chains=[]
legend=TLegend(0.5,0.5,0.8,0.8)

histnames = ['100-200', '200-300', '300-500', '500-700', '700-1000', '1000-1500', '1500-2000', '2000-inf']

for binn, sigma, numberOfEvent, hist in zip(binns, sigmas, numberOfEvents, histnames):
  print binn
  c=TChain("bhana/t")
  c.Add("root://eoscms.cern.ch/"+binn)
  hname="h"+str(len(histograms)) 
  c.Draw("ST>>"+hname+"(500,0,3000)")
  h=gPad.GetPrimitive(hname)
  h.Scale(sigma*100.0/numberOfEvent)
  h.SetFillColor(1+len(histograms))
  h.SetStats(kFALSE)
  stack.Add(h)
  histograms.append(h)
  legend.SetFillColor(0)
  legend.SetHeader("H_{T} bins at 13 TeV")
  legend.AddEntry(h, hist, "f")

stack.SetTitle("QCD sample summed over H_{T} bins; S_{T} [GeV]")
stack.Draw()
stack.SetMinimum(100)
stack.Draw()
legend.Draw()
c1.SaveAs("QCD_summed_13TeV.C")
c1.SaveAs("QCD_summed_13TeV.pdf")
c1.SaveAs("QCD_summed_13TeV.png")
