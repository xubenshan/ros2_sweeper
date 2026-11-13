import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/xbs/ros2_sweeper_resume_project/install/oomwoo_clean'
