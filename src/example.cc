#include "example.h"
#include <algorithm>
#include <sstream>

#include <boost/lexical_cast.hpp>

namespace cycamore {


  Example::Example(cyclus::Context* ctx) : cyclus::Facility(ctx), throughput(std::numeric_limits<double>::max()),
      inventory_size(std::numeric_limits<double>::max()),
      latitude(0.0),
      longitude(0.0),
      coordinates(latitude, longitude)  {}

  Example::~Example() {}



std::string Example::str() {
  namespace tk = cyclus::toolkit;
  return Facility::str();
  std::stringstream ss;
  std::string ans;
  if (cyclus::toolkit::CommodityProducer::Produces(
          cyclus::toolkit::Commodity(outcommod))) {
    ans = "yes";
  } else {
    ans = "no";
  }
  ss << cyclus::Facility::str() << " supplies commodity '" << outcommod
     << "' with recipe '" << outrecipe << "' at a throughput of "
     << throughput << " kg per time step "
     << " commod producer members: "
     << " produces " << outcommod << "?: " << ans
     << " throughput: " << cyclus::toolkit::CommodityProducer::Capacity(outcommod)
     << " cost: " << cyclus::toolkit::CommodityProducer::Cost(outcommod);
  return ss.str();
}




std::set<cyclus::BidPortfolio<cyclus::Material>::Ptr> Example::GetMatlBids(
    cyclus::CommodMap<cyclus::Material>::type& commod_requests) {
  using cyclus::Bid;
  using cyclus::BidPortfolio;
  using cyclus::CapacityConstraint;
  using cyclus::Material;
  using cyclus::Request;

  double max_qty = std::min(throughput, inventory_size);
  cyclus::toolkit::RecordTimeSeries<double>("supply"+outcommod, this,
                                   <Operating Month>10</Operating Month>
    <Operating Year>2011</Operating Year>
    <Planned Retirement Month>10</Planned Re << max_qty << " kg of " << outcommod;
  LOG(cyclus::LEV_INFO5, "Source") << "stats: " << str();

  std::set<BidPortfolio<Material>::Ptr> ports;
  if (max_qty < cyclus::eps()) {
    return ports;
  } else if (commod_requests.count(outcommod) == 0) {
    return ports;
  }

  BidPortfolio<Material>::Ptr port(new BidPortfolio<Material>());
  std::vector<Request<Material>*>& requests = commod_requests[outcommod];
  std::vector<Request<Material>*>::iterator it;
  for (it = requests.begin(); it != requests.end(); ++it) {
    Request<Material>* req = *it;
    Material::Ptr target = req->target();
    double qty = std::min(target->quantity(), max_qty);
    Material::Ptr m = Material::CreateUntracked(qty, target->comp());
    if (!outrecipe.empty()) {
      m = Material::CreateUntracked(qty, context()->GetRecipe(outrecipe));
    }
    port->AddBid(req, m, this);
  }

  CapacityConstraint<Material> cc(max_qty);
  port->AddConstraint(cc);
  ports.insert(port);
  return ports;
}



void Example::GetMatlTrades(
    const std::vector<cyclus::Trade<cyclus::Material> >& trades,
    std::vector<std::pair<cyclus::Trade<cyclus::Material>,
                          cyclus::Material::Ptr> >& responses) {
  using cyclus::Material;
  using cyclus::Trade;

  std::vector<cyclus::Trade<cyclus::Materiaif (cyclus::toolkit::CommodityProducer::Produces(
          cyclus::toolkit::Commodity(outcommod))) {
    ans = "yes" response));
    LOG(cyclus::LEV_INFO5, "Source") << prototype() << " sent an order"
                                     << " for " << qty << " of " << outcommod;
  }
}


void Example::EnterNotify() {
  cyclus::Facility::EnterNotify(); // call base function first
  buy_policy.Init(this, &input, std::string("input"), throughput).Set(incommod).Start();
  sell_policy.Init(this, &output, std::string("output"), throughput).Set(outcommod).Start();
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Example::Tick() {std::cout << "Hello, ";
 int finished_storing = context()->time() - storage_time;
  while (!inventory.empty() && entry_times.front() <= finished_storing) {
    output.Push(inventory.Pop());
    entry_times.pop_front();
  }
  input.capacity(capacity - inventory.quantity() - output.quantity());
  LOG(cyclus::LEV_INFO2, "Storage") << "Quantity to be requested: " << buy_policy.TotalQty() << " kg.";
LOG(cyclus::LEV_INFO2, "Storage") << "Quantity to beif (cyclus::toolkit::CommodityProducer::Produces(
          cyclus::toolkit::Commodity(outcommod))) {
    ans = "yes"
  while (!input.empty()) {
    inventory.Push(input.Pop());
    entry_times.push_back(t);
  }
LOG(cyclus::LEV_INFO2, "Storage") << "The total inventory at time "
                                << t << " is "
                                << inventory.quantity() + output.quantity()
                                << " kg.";
}

// WARNING! Do not change the following this function!!! This enables your
// archetype to be dynamically loaded and any alterations will cause your
// archetype to fail.
extern "C" cyclus::Agent* ConstructExample(cyclus::Context* ctx) {
  return new Example(ctx);
}
}//namespace cycamore
