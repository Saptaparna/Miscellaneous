import os
import string
#from decimal import *
#getcontext().prec = 6
N = 20
stepsize = 5
filenamR = "/uscms_data/d2/sapta/work/Snowmass_2013/v2/CMSSW_5_3_7_patch4/src/Generators/scripts/Hadronizer_MgmMatchTuneZ2star_generic.py"
fileext1 = ".py"
fileext2 = ".log"
filestring = "Hadronizer_MgmMatchTuneZ2star_generic"
readfile = open(filenamR,"r")
lines = readfile.read().splitlines()
qcut0 = 20
i=0
for i in range(N):
    qcut = qcut0 + i*stepsize
    filenamW = filestring + str(i+1) + fileext1
    writefile = open(filenamW,"w")
    for singline in lines:
        checkline = singline
        if(checkline=="        MEMAIN_qcut = cms.double(15),"):
            writefile.write("        MEMAIN_qcut = cms.double("+"%e"%qcut+"),\n")
        elif(checkline=="    fileName = cms.untracked.string('Hadronizer_MgmMatchTuneZ2star_8TeV_madgraph_cff_py_GEN_SIM.root'),"):
            writefile.write("    fileName = cms.untracked.string('Hadronizer_MgmMatchTuneZ2star_8TeV_madgraph_cff_py_GEN_SIM"+str(i+1)+".root'),\n")
        else:
            writefile.write(singline)
            writefile.write("\n")
readfile.close()
writefile.close()
env = {"PATH":"/uscms_data/d2/sapta/work/Snowmass_2013/v2/CMSSW_5_3_7_patch4/src/Generators/scripts/"}
comm = 'cmsRun'
for i in range(N):
    newfile = "Hadronizer_MgmMatchTuneZ2star_generic"+str(i+1)+fileext1
    comm = 'cmsRun '
    comm = comm+newfile
    comm1 = '> '
    newfile2 = "Hadronizer_MgmMatchTuneZ2star_generic"+str(i+1)+fileext2
    comm2 = comm1+newfile2
    commf = comm+comm1+newfile2 
    os.system(commf)
