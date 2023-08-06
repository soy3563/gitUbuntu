set_param project.enableReportConfiguration 0
load_feature core
current_fileset
xsim {tb_ledBlink} -wdb {simulate_xsim_tb_ledBlink.wdb} -autoloadwcfg
