#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to robot_cleaning_interfaces__msg__CleaningEvent

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CleaningEvent {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub sequence: u64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub severity: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub code: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub state: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub previous_state: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub recoverable: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub coverage: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub completed_waypoints: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub failed_waypoints: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub total_waypoints: u32,

}

impl CleaningEvent {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const INFO: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const WARNING: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const ERROR: u8 = 2;

}


impl Default for CleaningEvent {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::CleaningEvent::default())
  }
}

impl rosidl_runtime_rs::Message for CleaningEvent {
  type RmwMsg = super::msg::rmw::CleaningEvent;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        sequence: msg.sequence,
        severity: msg.severity,
        task_id: msg.task_id.as_str().into(),
        code: msg.code.as_str().into(),
        state: msg.state.as_str().into(),
        previous_state: msg.previous_state.as_str().into(),
        recoverable: msg.recoverable,
        message: msg.message.as_str().into(),
        coverage: msg.coverage,
        completed_waypoints: msg.completed_waypoints,
        failed_waypoints: msg.failed_waypoints,
        total_waypoints: msg.total_waypoints,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      sequence: msg.sequence,
      severity: msg.severity,
        task_id: msg.task_id.as_str().into(),
        code: msg.code.as_str().into(),
        state: msg.state.as_str().into(),
        previous_state: msg.previous_state.as_str().into(),
      recoverable: msg.recoverable,
        message: msg.message.as_str().into(),
      coverage: msg.coverage,
      completed_waypoints: msg.completed_waypoints,
      failed_waypoints: msg.failed_waypoints,
      total_waypoints: msg.total_waypoints,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      sequence: msg.sequence,
      severity: msg.severity,
      task_id: msg.task_id.to_string(),
      code: msg.code.to_string(),
      state: msg.state.to_string(),
      previous_state: msg.previous_state.to_string(),
      recoverable: msg.recoverable,
      message: msg.message.to_string(),
      coverage: msg.coverage,
      completed_waypoints: msg.completed_waypoints,
      failed_waypoints: msg.failed_waypoints,
      total_waypoints: msg.total_waypoints,
    }
  }
}


// Corresponds to robot_cleaning_interfaces__msg__CoverageStatus

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct CoverageStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub task_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub coverage: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub path_length_m: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub covered: nav_msgs::msg::OccupancyGrid,

}



impl Default for CoverageStatus {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::CoverageStatus::default())
  }
}

impl rosidl_runtime_rs::Message for CoverageStatus {
  type RmwMsg = super::msg::rmw::CoverageStatus;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        task_id: msg.task_id.as_str().into(),
        coverage: msg.coverage,
        path_length_m: msg.path_length_m,
        covered: nav_msgs::msg::OccupancyGrid::into_rmw_message(std::borrow::Cow::Owned(msg.covered)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        task_id: msg.task_id.as_str().into(),
      coverage: msg.coverage,
      path_length_m: msg.path_length_m,
        covered: nav_msgs::msg::OccupancyGrid::into_rmw_message(std::borrow::Cow::Borrowed(&msg.covered)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      task_id: msg.task_id.to_string(),
      coverage: msg.coverage,
      path_length_m: msg.path_length_m,
      covered: nav_msgs::msg::OccupancyGrid::from_rmw_message(msg.covered),
    }
  }
}


// Corresponds to robot_cleaning_interfaces__msg__LocalizationHealth

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct LocalizationHealth {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub state: u8,

    /// healthy means motion and coverage accounting may continue. A transient
    /// DEGRADED state remains operational until the configured loss hold expires.
    pub healthy: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub covariance_xy: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub lost_covariance_threshold: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub pose_age_s: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reason: std::string::String,

}

impl LocalizationHealth {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const UNKNOWN: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const HEALTHY: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const DEGRADED: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const LOST: u8 = 3;

}


impl Default for LocalizationHealth {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::LocalizationHealth::default())
  }
}

impl rosidl_runtime_rs::Message for LocalizationHealth {
  type RmwMsg = super::msg::rmw::LocalizationHealth;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        state: msg.state,
        healthy: msg.healthy,
        covariance_xy: msg.covariance_xy,
        lost_covariance_threshold: msg.lost_covariance_threshold,
        pose_age_s: msg.pose_age_s,
        reason: msg.reason.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      state: msg.state,
      healthy: msg.healthy,
      covariance_xy: msg.covariance_xy,
      lost_covariance_threshold: msg.lost_covariance_threshold,
      pose_age_s: msg.pose_age_s,
        reason: msg.reason.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      state: msg.state,
      healthy: msg.healthy,
      covariance_xy: msg.covariance_xy,
      lost_covariance_threshold: msg.lost_covariance_threshold,
      pose_age_s: msg.pose_age_s,
      reason: msg.reason.to_string(),
    }
  }
}


