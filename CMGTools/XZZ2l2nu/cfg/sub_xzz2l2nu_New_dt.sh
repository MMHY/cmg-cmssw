#!/bin/sh

heppy_batch.py -o LSF_dt run_xzz2l2nu_New_cfg_dt.py -b 'bsub -q 1nd < ./batchScript.sh'

#heppy New_2l2nu_mu run_xzz2l2nu_New_cfg.py
#heppy New_2ljet_el run_xzz2l2nu_New_cfg.py
#heppy New_2ljet run_xzz2l2nu_New_cfg.py
#heppy data_prmpv4 run_xzz2l2nu_cfg.py 
#heppy data_elrecoD  run_xzz2l2nu_cfg_1.py 
