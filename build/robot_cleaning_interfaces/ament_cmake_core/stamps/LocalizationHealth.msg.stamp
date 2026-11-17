std_msgs/Header header

uint8 UNKNOWN=0
uint8 HEALTHY=1
uint8 DEGRADED=2
uint8 LOST=3
uint8 state

# healthy means motion and coverage accounting may continue. A transient
# DEGRADED state remains operational until the configured loss hold expires.
bool healthy
float64 covariance_xy
float64 lost_covariance_threshold
float64 pose_age_s
string reason
