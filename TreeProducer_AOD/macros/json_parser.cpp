#include <iostream>
#include <string>
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"
#include "boost/optional/optional.hpp"
using namespace std;

bool Check_Run_Lumi(const int , const int );

int json_parser() {
  cout<<Check_Run_Lumi(273730, 1)<<endl;
  cout<<Check_Run_Lumi(273730, 2)<<endl;
  cout<<Check_Run_Lumi(273730, 1814)<<endl;
  cout<<Check_Run_Lumi(273730, 1815)<<endl;
  cout<<Check_Run_Lumi(2, 1815)<<endl;


  //273725": [[83, 252], [254, 2545]],
  cout<<Check_Run_Lumi(273725, 255)<<endl;
  cout<<Check_Run_Lumi(273725, 254)<<endl;
  cout<<Check_Run_Lumi(273725, 253)<<endl;
  cout<<Check_Run_Lumi(0, 0)<<endl;

  return 0;
}


bool Check_Run_Lumi(const int run, const int lumi_n){

  using boost::property_tree::ptree;

  // Short alias for boost namespace
  namespace pt = boost::property_tree;

  // Create a root
  pt::ptree root;

  // Load the json file in this ptree
  pt::read_json("Cert_271036-284044_13TeV_PromptReco_Collisions16_JSON.txt", root);

  std::string run_n = std::to_string(run);

  vector<pair<int, int> > lumis;

  ///Check if run exists - if not return false
  boost::optional< ptree& > child = root.get_child_optional( run_n );
  if(!child) return false;

  ///Store pair of lumis in a vector
  for (pt::ptree::value_type &row : root.get_child(run_n))
  {
      int ll[2];
      int x = 0;
      for (pt::ptree::value_type &cell : row.second)
      {
          ll[x] = cell.second.get_value<int>();
          x++;
      }
      std::pair <int, int> lumi = std::make_pair( ll[0], ll[1] );
      lumis.push_back(lumi);
  }

  ///Check if lumi is within the pairs
  for(unsigned int i = 0; i<lumis.size(); i++){
    if(lumi_n>=lumis[i].first && lumi_n<=lumis[i].second) return true;
  }

  return false;

}
