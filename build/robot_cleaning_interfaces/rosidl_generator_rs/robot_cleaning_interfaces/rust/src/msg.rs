#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



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


