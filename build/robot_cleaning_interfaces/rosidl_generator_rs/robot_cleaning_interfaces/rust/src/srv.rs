#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};




// Corresponds to robot_cleaning_interfaces__srv__BeginCoverage_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct BeginCoverage_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub task_id: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub regions: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub start: geometry_msgs::msg::PoseStamped,


    // This member is not documented.
    #[allow(missing_docs)]
    pub restored_grid: Vec<i8>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub restored_distance_m: f64,

}



impl Default for BeginCoverage_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::BeginCoverage_Request::default())
  }
}

impl rosidl_runtime_rs::Message for BeginCoverage_Request {
  type RmwMsg = super::srv::rmw::BeginCoverage_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        task_id: msg.task_id.as_str().into(),
        regions: msg.regions
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        start: geometry_msgs::msg::PoseStamped::into_rmw_message(std::borrow::Cow::Owned(msg.start)).into_owned(),
        restored_grid: msg.restored_grid.as_slice().into(),
        restored_distance_m: msg.restored_distance_m,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        task_id: msg.task_id.as_str().into(),
        regions: msg.regions
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        start: geometry_msgs::msg::PoseStamped::into_rmw_message(std::borrow::Cow::Borrowed(&msg.start)).into_owned(),
        restored_grid: msg.restored_grid.as_slice().into(),
      restored_distance_m: msg.restored_distance_m,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      task_id: msg.task_id.to_string(),
      regions: msg.regions
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      start: geometry_msgs::msg::PoseStamped::from_rmw_message(msg.start),
      restored_grid: msg.restored_grid.into(),
      restored_distance_m: msg.restored_distance_m,
    }
  }
}


// Corresponds to robot_cleaning_interfaces__srv__BeginCoverage_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct BeginCoverage_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reason: std::string::String,

}



impl Default for BeginCoverage_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::BeginCoverage_Response::default())
  }
}

impl rosidl_runtime_rs::Message for BeginCoverage_Response {
  type RmwMsg = super::srv::rmw::BeginCoverage_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        reason: msg.reason.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
        reason: msg.reason.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      reason: msg.reason.to_string(),
    }
  }
}


// Corresponds to robot_cleaning_interfaces__srv__ListCleaningEvents_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ListCleaningEvents_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub limit: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub task_id_filter: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub code_filter: std::string::String,

}



impl Default for ListCleaningEvents_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::ListCleaningEvents_Request::default())
  }
}

impl rosidl_runtime_rs::Message for ListCleaningEvents_Request {
  type RmwMsg = super::srv::rmw::ListCleaningEvents_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        limit: msg.limit,
        task_id_filter: msg.task_id_filter.as_str().into(),
        code_filter: msg.code_filter.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      limit: msg.limit,
        task_id_filter: msg.task_id_filter.as_str().into(),
        code_filter: msg.code_filter.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      limit: msg.limit,
      task_id_filter: msg.task_id_filter.to_string(),
      code_filter: msg.code_filter.to_string(),
    }
  }
}


// Corresponds to robot_cleaning_interfaces__srv__ListCleaningEvents_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ListCleaningEvents_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub events: Vec<super::msg::CleaningEvent>,

}



impl Default for ListCleaningEvents_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::ListCleaningEvents_Response::default())
  }
}

impl rosidl_runtime_rs::Message for ListCleaningEvents_Response {
  type RmwMsg = super::srv::rmw::ListCleaningEvents_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        message: msg.message.as_str().into(),
        events: msg.events
          .into_iter()
          .map(|elem| super::msg::CleaningEvent::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
        message: msg.message.as_str().into(),
        events: msg.events
          .iter()
          .map(|elem| super::msg::CleaningEvent::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      message: msg.message.to_string(),
      events: msg.events
          .into_iter()
          .map(super::msg::CleaningEvent::from_rmw_message)
          .collect(),
    }
  }
}


// Corresponds to robot_cleaning_interfaces__srv__PlanCoverage_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PlanCoverage_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub regions: Vec<std::string::String>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub start: geometry_msgs::msg::PoseStamped,


    // This member is not documented.
    #[allow(missing_docs)]
    pub gap_fill: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub target_coverage: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub distance_budget_m: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub covered: nav_msgs::msg::OccupancyGrid,


    // This member is not documented.
    #[allow(missing_docs)]
    pub excluded: Vec<geometry_msgs::msg::Point>,

}



impl Default for PlanCoverage_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::PlanCoverage_Request::default())
  }
}

impl rosidl_runtime_rs::Message for PlanCoverage_Request {
  type RmwMsg = super::srv::rmw::PlanCoverage_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        regions: msg.regions
          .into_iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        start: geometry_msgs::msg::PoseStamped::into_rmw_message(std::borrow::Cow::Owned(msg.start)).into_owned(),
        gap_fill: msg.gap_fill,
        target_coverage: msg.target_coverage,
        distance_budget_m: msg.distance_budget_m,
        covered: nav_msgs::msg::OccupancyGrid::into_rmw_message(std::borrow::Cow::Owned(msg.covered)).into_owned(),
        excluded: msg.excluded
          .into_iter()
          .map(|elem| geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        regions: msg.regions
          .iter()
          .map(|elem| elem.as_str().into())
          .collect(),
        start: geometry_msgs::msg::PoseStamped::into_rmw_message(std::borrow::Cow::Borrowed(&msg.start)).into_owned(),
      gap_fill: msg.gap_fill,
      target_coverage: msg.target_coverage,
      distance_budget_m: msg.distance_budget_m,
        covered: nav_msgs::msg::OccupancyGrid::into_rmw_message(std::borrow::Cow::Borrowed(&msg.covered)).into_owned(),
        excluded: msg.excluded
          .iter()
          .map(|elem| geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      regions: msg.regions
          .into_iter()
          .map(|elem| elem.to_string())
          .collect(),
      start: geometry_msgs::msg::PoseStamped::from_rmw_message(msg.start),
      gap_fill: msg.gap_fill,
      target_coverage: msg.target_coverage,
      distance_budget_m: msg.distance_budget_m,
      covered: nav_msgs::msg::OccupancyGrid::from_rmw_message(msg.covered),
      excluded: msg.excluded
          .into_iter()
          .map(geometry_msgs::msg::Point::from_rmw_message)
          .collect(),
    }
  }
}


// Corresponds to robot_cleaning_interfaces__srv__PlanCoverage_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PlanCoverage_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub reason: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub path: nav_msgs::msg::Path,

}



impl Default for PlanCoverage_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::PlanCoverage_Response::default())
  }
}

impl rosidl_runtime_rs::Message for PlanCoverage_Response {
  type RmwMsg = super::srv::rmw::PlanCoverage_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        success: msg.success,
        reason: msg.reason.as_str().into(),
        path: nav_msgs::msg::Path::into_rmw_message(std::borrow::Cow::Owned(msg.path)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      success: msg.success,
        reason: msg.reason.as_str().into(),
        path: nav_msgs::msg::Path::into_rmw_message(std::borrow::Cow::Borrowed(&msg.path)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      success: msg.success,
      reason: msg.reason.to_string(),
      path: nav_msgs::msg::Path::from_rmw_message(msg.path),
    }
  }
}






#[link(name = "robot_cleaning_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__robot_cleaning_interfaces__srv__BeginCoverage() -> *const std::ffi::c_void;
}

// Corresponds to robot_cleaning_interfaces__srv__BeginCoverage
#[allow(missing_docs, non_camel_case_types)]
pub struct BeginCoverage;

impl rosidl_runtime_rs::Service for BeginCoverage {
    type Request = BeginCoverage_Request;
    type Response = BeginCoverage_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__robot_cleaning_interfaces__srv__BeginCoverage() }
    }
}




#[link(name = "robot_cleaning_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__robot_cleaning_interfaces__srv__ListCleaningEvents() -> *const std::ffi::c_void;
}

// Corresponds to robot_cleaning_interfaces__srv__ListCleaningEvents
#[allow(missing_docs, non_camel_case_types)]
pub struct ListCleaningEvents;

impl rosidl_runtime_rs::Service for ListCleaningEvents {
    type Request = ListCleaningEvents_Request;
    type Response = ListCleaningEvents_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__robot_cleaning_interfaces__srv__ListCleaningEvents() }
    }
}




#[link(name = "robot_cleaning_interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__robot_cleaning_interfaces__srv__PlanCoverage() -> *const std::ffi::c_void;
}

// Corresponds to robot_cleaning_interfaces__srv__PlanCoverage
#[allow(missing_docs, non_camel_case_types)]
pub struct PlanCoverage;

impl rosidl_runtime_rs::Service for PlanCoverage {
    type Request = PlanCoverage_Request;
    type Response = PlanCoverage_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__robot_cleaning_interfaces__srv__PlanCoverage() }
    }
}


