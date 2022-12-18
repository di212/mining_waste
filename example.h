#ifndef CYCAMORE_SRC_EXAMPLE_H
#define CYCAMORE_SRC_EXAMPLE_H
#include <set>
#include <vector>
#include <string>
#include <list>
#include "cyclus.h"
#include "cycamore_version.h"
namespace cycamore {
class Context; 

/// @class Example
///
/// This Facility is intended
/// as a skeleton to guide the implementation of new Facility
/// agents.
/// The TutorialFacility class inherits from the Facility class and is
/// dynamically loaded by the Agent class when requested.
///
/// @section intro Introduction
/// Place an introduction to the agent here.
///
/// @section agentparams Agent Parameters
/// Place a description of the required input parameters which define the
/// agent implementation.
///
/// @section optionalparams Optional Parameters
/// Place a description of the optional input parameters to define the
/// agent implementation.
///
/// @section detailed Detailed Behavior
/// Place a description of the detailed behavior of the agent. Consider
/// describing the behavior at the tick and tock as well as the behavior
/// upon sending and receiving materials and messages.
  class Example 
  : public cyclus::Facility,
    public cyclus::toolkit::CommodityProducer,
    public cyclus::toolkit::Position  {
 public:
  /// Constructor for TutorialFacility Class
  /// @param ctx the cyclus context for access to simulation-wide parameters
  Example(cyclus::Context* ctx);
  virtual ~Example();

  /// The Prime Directive
  /// Generates code that handles all input file reading and restart operations
  /// (e.g., reading from the database, instantiating a new object, etc.).
  /// @warning The Prime Directive must have a space before it! (A fix will be
  /// in 2.0 ^TM)
  virtual std::string version() { return CYCAMORE_VERSION; }
  #pragma cyclus

  #pragma cyclus note {"doc": "A tutorial facility is provided as a skeleton " \
                              "for the design of new facility agents."}



 virtual std::set<cyclus::BidPortfolio<cyclus::Material>::Ptr>
    GetMatlBids(cyclus::CommodMap<cyclus::Material>::type&
                commod_requests);

virtual void GetMatlTrades(
    const std::vector< cyclus::Trade<cyclus::Material> >& trades,
    std::vector<std::pair<cyclus::Trade<cyclus::Material>,
    cyclus::Material::Ptr> >& responses);
  



  /// A verbose printer for the TutorialFacility
  virtual std::string str();
  /// set up policies and buffers
  virtual void EnterNotify();

  /// The handleTick function specific to the TutorialFacility.
  /// @param time the time of the tick
  virtual void Tick();

  /// The handleTick function specific to the TutorialFacility.
  /// @param time the time of the tock
  virtual void Tock();

  #pragma cyclus var {"default": 1e299,\
  "doc": "Maximum amount of material that can be transferred in or out each time step", \
  "tooltip": "Maximum amount of material that can be transferred in or out each time step", \
  "units": "kg", \
  "uitype": "range", \
  "range": [0.0, 1e299], \
  "uilabel": "Maximum Throughput" \
}
double throughput;
#pragma cyclus var { \
  'doc': 'Maximum storage capacity (including all material in the facility)', \
  'tooltip': 'Maximum storage capacity', \
  'units': 'kg', \
  'default': 1e200, \
  'uilabel': 'Maximum Storage Capacity' \
}
double capacity;
#pragma cyclus var { \
  "doc": "Minimum amount of time material must be stored", \
  "tooltip": "Minimum amount of time material must be stored", \
  "units": "months", \
  "uilabel": "Storage Time" \
}
int storage_time;

#pragma cyclus var { \
 "tooltip": "Storage input commodity", \
 "doc": "Input commodity on which Storage requests material.", \
 "uilabel": "Input Commodity", \
 "uitype": "incommodity", \
}
std::string incommod;

#pragma cyclus var { \
 "tooltip": "Storage output commodity", \
 "doc": "Output commodity on which Storage offers material.", \
 "uilabel": "Output Commodity", \
 "uitype": "outcommodity", \
}
std::string outcommod;
#pragma cyclus var { \
    "tooltip": "name of material recipe to provide", \
    "doc": "Name of composition recipe that this source provides regardless " \
           "of requested composition. If empty, source creates and provides " \
           "whatever compositions are requested.", \
    "uilabel": "Output Recipe", \
    "default": "", \
    "uitype": "outrecipe", \
  }
  std::string outrecipe;

  #pragma cyclus var { \
  "doc": "Total amount of material this source has remaining." \
          " Every trade decreases this value by the supplied material " \
          "quantity.  When it reaches zero, the source cannot provide any " \
          " more material.", \
  "default": 1e299, \
  "uitype": "range", \
  "range": [0.0, 1e299], \
  "uilabel": "Initial Inventory", \
  "units": "kg", \
  }
  double inventory_size;
  #pragma cyclus var { \
  "default": 0.0, \
  "uilabel": "Geographical latitude in degrees as a double", \
  "doc": "Latitude of the agent's geographical position. The value should " \
          "be expressed in degrees as a double." \
  }
  double latitude;

  #pragma cyclus var { \
    "default": 0.0, \
    "uilabel": "Geographical longitude in degrees as a double", \
    "doc": "Longitude of the agent's geographical position. The value should " \
           "be expressed in degrees as a double." \
  }
  double longitude;

  cyclus::toolkit::Position coordinates;
  void RecordPosition();


/// this facility holds material in storage.
#pragma cyclus var {}
cyclus::toolkit::ResBuf<cyclus::Material> inventory;
/// a buffer for incoming material
#pragma cyclus var {}
cyclus::toolkit::ResBuf<cyclus::Material> input;

/// a buffer for outgoing material
#pragma cyclus var {}
cyclus::toolkit::ResBuf<cyclus::Material> output;
/// a policy for requesting material
cyclus::toolkit::MatlBuyPolicy buy_policy;

/// a policy for sending material
cyclus::toolkit::MatlSellPolicy sell_policy;

/// list for material entry times, providing a default lets this variable be
/// optional in an input file
#pragma cyclus var {"default": [] \
}
std::list<int> entry_times;


  // And away we go!
};

}  // namespace cycamore

#endif  // CYCAMORE_SRC_EXAMPLE_H
