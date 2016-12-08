#include <iostream>

#include "Analysis/VLQAna/interface/PickGenPart.h"

using namespace edm;

PickGenPart::PickGenPart (const edm::ParameterSet& iConfig, edm::ConsumesCollector && iC) :
  t_genparticles       (iC.consumes<std::vector<reco::GenParticle>>(iConfig.getParameter<edm::InputTag>("genParticles"))),
  t_genPartID          (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartID"))), 
  t_genPartStatus      (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartStatus"))),
  t_genPartMom0ID      (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartMom0ID"))), 
  t_genPartMom1ID      (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartMom1ID"))), 
  t_genPartMom0Status  (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartMom0Status"))), 
  t_genPartMom1Status  (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartMom1Status"))), 
  t_genPartDau0ID      (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartDau0ID"))), 
  t_genPartDau1ID      (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartDau1ID"))), 
  t_genPartDau0Status  (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartDau0Status"))), 
  t_genPartDau1Status  (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartDau1Status"))), 
  t_genPartPt          (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartPt"))), 
  t_genPartEta         (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartEta"))), 
  t_genPartPhi         (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartPhi"))), 
  t_genPartMass        (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartMass"))), 
  t_genPartE           (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartE"))), 
  t_genPartCharge      (iC.consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("genPartCharge"))), 
  ids_                 (iConfig.getParameter<std::vector<int>>("ids")), 
  statuses_            (iConfig.getParameter<std::vector<int>>("statuses")), 
  checkstatus_         (iConfig.getParameter<bool>("checkstatus")), 
  mom0ids_             (iConfig.getParameter<std::vector<int>>("mom0ids")), 
  mom1ids_             (iConfig.getParameter<std::vector<int>>("mom1ids")), 
  checkmomid_          (iConfig.getParameter<bool>("checkmomid")),
  dau0ids_             (iConfig.getParameter<std::vector<int>>("dau0ids")), 
  dau1ids_             (iConfig.getParameter<std::vector<int>>("dau1ids")), 
  checkdauid_          (iConfig.getParameter<bool>("checkdauid")),
  debug_               (iConfig.getParameter<bool>("debug"))
{ 
}

PickGenPart::~PickGenPart () {}

// this is modified for the new format of the b2g ntuples
const GenParticleCollection PickGenPart::operator() ( edm::Event& evt) {

    using namespace std;
    
    edm::Handle<std::vector<reco::GenParticle>> h_genparticles;
    evt.getByToken(t_genparticles, h_genparticles);
    
    genParts_.clear();
    
    /*
    if ( true ) {
        for ( reco::GenParticle igen : *(h_genparticles.product())) {
            std::cout << " pdg id = " << igen.pdgId() << std::endl ;
            std::cout << " pt     = " << igen.pt() << std::endl ;
            std::cout << " eta    = " << igen.eta() << std::endl ;
            std::cout << " phi    = " << igen.phi() << std::endl ;
            std::cout << " e      = " << igen.energy() << std::endl ;
            std::cout << " mass   = " << igen.mass() << std::endl ;
            
            std::cout << " nmoms = " << igen.numberOfMothers() << " ndaus = " << igen.numberOfDaughters() << std::endl;
            
            if (igen.numberOfMothers() > 0 && igen.mother(0) != nullptr) {
                std::cout << " mom pdg id = " << igen.mother(0)->pdgId() << std::endl ;
                std::cout << " mom pt     = " << igen.mother(0)->pt() << std::endl ;
                std::cout << " mom eta    = " << igen.mother(0)->eta() << std::endl ;
                std::cout << " mom phi    = " << igen.mother(0)->phi() << std::endl ;
                std::cout << " mom e      = " << igen.mother(0)->energy() << std::endl ;
                std::cout << " mom mass   = " << igen.mother(0)->mass() << std::endl ;
            }
            
            if (igen.numberOfDaughters() > 0 && igen.daughter(0) != nullptr) {
                std::cout << " dau0 pdg id = " << igen.daughter(0)->pdgId() << std::endl ;
                std::cout << " dau0 pt     = " << igen.daughter(0)->pt() << std::endl ;
                std::cout << " dau0 eta    = " << igen.daughter(0)->eta() << std::endl ;
                std::cout << " dau0 phi    = " << igen.daughter(0)->phi() << std::endl ;
                std::cout << " dau0 e      = " << igen.daughter(0)->energy() << std::endl ;
                std::cout << " dau0 mass   = " << igen.daughter(0)->mass() << std::endl ; 
            }
        }
    }
    */

    return genParts_ ;
}
