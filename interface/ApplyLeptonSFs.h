#ifndef ANALYSIS_VLQANA_APPLYLEPTONSFS_HH
#define ANALYSIS_VLQANA_APPLYLEPTONSFS_HH

class ApplyLeptonSFs {
  public:
    enum LEPTONIDTYPES_t {LOOSE, TIGHT} ; 
    ApplyLeptonSFs (edm::ParameterSet const& pars) : 
      sf_(1),
      zdecayMode_(pars.getParameter<std::string>("zdecayMode"))
  {
     std::string lepidtypestr = pars.getParameter<std::string>("lepidtype") ; 
     if ( lepidtypestr == "LOOSE" ) type_ = LOOSE ;  
     else if ( lepidtypestr == "TIGHT" ) type_ = TIGHT ; 
     else edm::LogError("ApplyLeptonSF") << " >>>> WrongElectronIdType: " << type_<< " Check lepton id type !!!" ; 
  }
    ~ApplyLeptonSFs () {} 
    double operator () (double pt, double eta){
       if (type_ == TIGHT && zdecayMode_ == "wel"){
          if(pt > 100.) pt = 100.;
          if(pt > 40 && pt <= 50){
             if(eta <= -2.0          && eta > -2.5)    sf_ =  0.943;
             else if(eta <= -1.566   && eta > -2.0)    sf_ =  0.933;
             else if(eta <= -1.4442  && eta > -1.566)  sf_ =  0.945;
             else if(eta <= -0.8     && eta > -1.4442) sf_ =  0.953;
             else if(eta <= 0.0      && eta > -0.8)    sf_ =  0.933;
             else if(eta <= 0.8      && eta > 0.0)     sf_ =  0.954;
             else if(eta <= 1.4442   && eta > 0.8)     sf_ =  0.945;
             else if(eta <= 1.566    && eta > 1.4442)  sf_ =  0.927;
             else if(eta <= 2.0      && eta > 1.566)   sf_ =  0.938;
             else if(eta < 2.5       && eta > 2.0)     sf_ =  0.943;
          }
          else if(pt > 50){
             if(eta <= -2.0          && eta > -2.5)    sf_ =  0.954;
             else if(eta <= -1.566   && eta > -2.0)    sf_ =  0.947;
             else if(eta <= -1.4442  && eta > -1.566)  sf_ =  0.957;
             else if(eta <= -0.8     && eta > -1.4442) sf_ =  0.953;
             else if(eta <= 0.0      && eta > -0.8)    sf_ =  0.939;
             else if(eta <= 0.8      && eta > 0.0)     sf_ =  0.954;
             else if(eta <= 1.4442   && eta > 0.8)     sf_ =  0.954;
             else if(eta <= 1.566    && eta > 1.4442)  sf_ =  0.936;
             else if(eta <= 2.0      && eta > 1.566)   sf_ =  0.968;
             else if(eta < 2.5       && eta > 2.0)     sf_ =  0.949;
          }else{
              
              sf_ = 1.0;
          }
       }//end TIGHT and zelel
       if (type_ == LOOSE  && zdecayMode_ == "wel"){
          if(pt > 100.) pt = 100.; 
          if(pt > 10 && pt <= 20){
             if(eta <= -2.0          && eta > -2.5)    sf_ =  1.11;
             else if(eta <= -1.566   && eta > -2.0)    sf_ =  1.08;
             else if(eta <= -1.4442  && eta > -1.566)  sf_ =  1.14;
             else if(eta <= -0.8     && eta > -1.4442) sf_ =  1.10;
             else if(eta <= 0.0      && eta > -0.8)    sf_ =  1.01;
             else if(eta <= 0.8      && eta > 0.0)     sf_ =  1.11;
             else if(eta <= 1.4442   && eta > 0.8)     sf_ =  1.14;
             else if(eta <= 1.566    && eta > 1.4442)  sf_ =  1.22;
             else if(eta <= 2.0      && eta > 1.566)   sf_ =  1.08;
             else if(eta < 2.5       && eta > 2.0)     sf_ =  1.07;
          }
          else if(pt > 20 && pt <= 30){
             if(eta <= -2.0          && eta > -2.5)    sf_ =  1.00;
             else if(eta <= -1.566   && eta > -2.0)    sf_ =  1.06;
             else if(eta <= -1.4442  && eta > -1.566)  sf_ =  1.15;
             else if(eta <= -0.8     && eta > -1.4442) sf_ =  1.07;
             else if(eta <= 0.0      && eta > -0.8)    sf_ =  1.03;
             else if(eta <= 0.8      && eta > 0.0)     sf_ =  1.00;
             else if(eta <= 1.4442   && eta > 0.8)     sf_ =  0.97;
             else if(eta <= 1.566    && eta > 1.4442)  sf_ =  1.13;
             else if(eta <= 2.0      && eta > 1.566)   sf_ =  1.03;
             else if(eta < 2.5       && eta > 2.0)     sf_ =  1.04;
          }
          else if(pt > 30 && pt <= 40){
             if(eta <= -2.0          && eta > -2.5)    sf_ =  1.02;
             else if(eta <= -1.566   && eta > -2.0)    sf_ =  1.00;
             else if(eta <= -1.4442  && eta > -1.566)  sf_ =  0.93;
             else if(eta <= -0.8     && eta > -1.4442) sf_ =  1.01;
             else if(eta <= 0.0      && eta > -0.8)    sf_ =  0.99;
             else if(eta <= 0.8      && eta > 0.0)     sf_ =  1.00;
             else if(eta <= 1.4442   && eta > 0.8)     sf_ =  1.00;
             else if(eta <= 1.566    && eta > 1.4442)  sf_ =  0.95;
             else if(eta <= 2.0      && eta > 1.566)   sf_ =  0.95;
             else if(eta < 2.5       && eta > 2.0)     sf_ =  1.03;
          }
          else if(pt > 40 && pt <= 50){
             if(eta <= -2.0          && eta > -2.5)    sf_ =  1.01;
             else if(eta <= -1.566   && eta > -2.0)    sf_ =  1.01;
             else if(eta <= -1.4442  && eta > -1.566)  sf_ =  1.02;
             else if(eta <= -0.8     && eta > -1.4442) sf_ =  0.99;
             else if(eta <= 0.0      && eta > -0.8)    sf_ =  0.99;
             else if(eta <= 0.8      && eta > 0.0)     sf_ =  0.99;
             else if(eta <= 1.4442   && eta > 0.8)     sf_ =  1.00;
             else if(eta <= 1.566    && eta > 1.4442)  sf_ =  1.01;
             else if(eta <= 2.0      && eta > 1.566)   sf_ =  1.01;
             else if(eta < 2.5       && eta > 2.0)     sf_ =  1.00;
          }
          else if(pt > 50 && pt <= 100){
             if(eta <= -2.0          && eta > -2.5)    sf_ =  1.00;
             else if(eta <= -1.566   && eta > -2.0)    sf_ =  1.01;
             else if(eta <= -1.4442  && eta > -1.566)  sf_ =  1.02;
             else if(eta <= -0.8     && eta > -1.4442) sf_ =  1.00;
             else if(eta <= 0.0      && eta > -0.8)    sf_ =  1.00;
             else if(eta <= 0.8      && eta > 0.0)     sf_ =  1.00;
             else if(eta <= 1.4442   && eta > 0.8)     sf_ =  0.98;
             else if(eta <= 1.566    && eta > 1.4442)  sf_ =  0.91;
             else if(eta <= 2.0      && eta > 1.566)   sf_ =  0.99;
             else if(eta < 2.5       && eta > 2.0)     sf_ =  1.01;
          }
       }//end LOOSE and zelel
       if (type_ == LOOSE && zdecayMode_ == "wmu"){
          if(pt > 120.) pt = 120.;
          if (pt > 40 && pt <= 50){
             if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.9989;
             else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.9995;
             else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.9981;
             else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.9959;
          }
          else if (pt > 50 && pt <= 60){
             if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.9947;
             else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.9975;
             else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.9992;
             else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.9911;
          }
          else if (pt > 60 && pt <= 120){
             if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.9995;
             else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 1.0026;
             else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.9996;
             else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.99978;
          }  
       }//LOOSE and zmumu
       if (type_ == TIGHT && zdecayMode_ == "wmu"){
          if(pt > 500) pt = 500;
          if (pt > 40 && pt <= 50){                               // ID x ISO x Trigger[this is efficiency in data, and not data/MC SFs]
             if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.969 * 0.996 * 0.826;
             else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.991 * 0.998 * 0.890;
             else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.971 * 0.998 * 0.933;
             else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.976 * 0.994 * 0.934;
          }
          else if (pt > 50 && pt <= 60){
             if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.981 * 0.998 * 0.829;
             else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.992 * 0.998 * 0.893;
             else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.971 * 0.999 * 0.936;
             else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.972 * 0.999 * 0.937;
          }
          else if (pt > 60 && pt <= 120){
             if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.975 * 1.000 * 0.829;
             else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 0.989 * 0.998 * 0.890;
             else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 0.968 * 0.999 * 0.934;
             else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.973 * 0.999 * 0.934;
          }
          else if (pt > 120 && pt <= 200){
              if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.918 * 0.998 * 0.799;
              else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 1.013 * 1.001 * 0.838;
              else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 1.027 * 0.996 * 0.916;
              else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.987 * 1.000 * 0.932;
          }
          else if (pt > 200 && pt <= 500){
              if (abs(eta) <= 2.4 && abs(eta) > 2.1)       sf_ = 0.918 * 0.998 * 0.689;
              else if (abs(eta) <= 2.1 && abs(eta) > 1.2)  sf_ = 1.013 * 1.001 * 0.725;
              else if (abs(eta) <= 1.2 && abs(eta) > 0.9)  sf_ = 1.027 * 0.996 * 0.884;
              else if (abs(eta) <= 0.9 && abs(eta) > 0.0)  sf_ = 0.987 * 1.000 * 0.919;
          }
          else{
              sf_ = 1.0;
          }
       }//TIGHT and zmumu
       return sf_ ; 
    }
  private: 
    double sf_ ;
    const std::string zdecayMode_ ;
    LEPTONIDTYPES_t type_ ; 
};
#endif 
