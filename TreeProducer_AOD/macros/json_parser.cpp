#include <iostream>
#include <string>
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/json_parser.hpp"
#include "boost/optional/optional.hpp"

#include <ctime>

using namespace std;
using boost::property_tree::ptree;
namespace pt = boost::property_tree;

bool Check_Run_Lumi(const int , const int , pt::ptree);

int json_parser() {

  pt::ptree root;
  pt::read_json("Cert_271036-284044_13TeV_PromptReco_Collisions16_JSON.txt", root);


  cout<<Check_Run_Lumi(273730, 1, root)<<endl;
  cout<<Check_Run_Lumi(273730, 2, root)<<endl;
  cout<<Check_Run_Lumi(273730, 1814, root)<<endl;
  cout<<Check_Run_Lumi(273730, 1815, root)<<endl;
  cout<<Check_Run_Lumi(2, 1815, root)<<endl;


  //273725": [[83, 252], [254, 2545]],
  cout<<Check_Run_Lumi(273725, 255, root)<<endl;
  cout<<Check_Run_Lumi(273725, 254, root)<<endl;
  cout<<Check_Run_Lumi(273725, 253, root)<<endl;


  // clock_t begin = clock();
  // for(int i=0; i<50000; i++){
  //   Check_Run_Lumi(i, i, root);
  // }
  // clock_t end = clock();
  // double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  // cout<<"time  "<<elapsed_secs<<endl;


  return 0;
}


bool Check_Run_Lumi(const int run, const int lumi_n, pt::ptree root){

  std::string run_n = std::to_string(run);


  ///Check if run exists - if not return false
  boost::optional< ptree& > child = root.get_child_optional( run_n );
  if(!child) return false;

  vector<pair<int, int> > lumis;
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
