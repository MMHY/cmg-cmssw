#include "DataFormats/JetReco/interface/Jet.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DQMOffline/PFTau/interface/Matchers.h"

#include "DQMOffline/PFTau/interface/PFJetMonitor.h"

#include <TROOT.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
//
// -- Constructor
//
PFJetMonitor::PFJetMonitor( float dRMax, bool matchCharge, Benchmark::Mode mode) : 
  Benchmark(mode), 
  candBench_(mode), 
  matchCandBench_(mode), 
  dRMax_(dRMax), 
  matchCharge_(matchCharge) {
  
  setRange( 0.0, 10e10, -10.0, 10.0, -3.14, 3.14);
  
  delta_frac_VS_frac_muon_           = 0;
  delta_frac_VS_frac_photon_         = 0;
  delta_frac_VS_frac_electron_       = 0;
  delta_frac_VS_frac_charged_hadron_ = 0;
  delta_frac_VS_frac_neutral_hadron_ = 0;
  
  createPFractionHistos_ = false;
  histogramBooked_ = false;
}
//
// -- Destructor
//
PFJetMonitor::~PFJetMonitor() {}

//
// -- Set Parameters accessing them from ParameterSet
//
void PFJetMonitor::setParameters( const edm::ParameterSet & parameterSet) {

  dRMax_                 = parameterSet.getParameter<double>( "deltaRMax" );
  matchCharge_           = parameterSet.getParameter<bool>( "matchCharge" );
  mode_                  = (Benchmark::Mode) parameterSet.getParameter<int>( "mode" );
  createPFractionHistos_ = parameterSet.getParameter<bool>( "CreatePFractionHistos" );

  
  setRange( parameterSet.getParameter<double>("ptMin"),
	    parameterSet.getParameter<double>("ptMax"),
	    parameterSet.getParameter<double>("etaMin"),
	    parameterSet.getParameter<double>("etaMax"),
	    parameterSet.getParameter<double>("phiMin"),
	    parameterSet.getParameter<double>("phiMax") );

  candBench_.setParameters(mode_);
  matchCandBench_.setParameters(mode_);
}
//
// -- Set Parameters 
//
void PFJetMonitor::setParameters(float dRMax, bool matchCharge, Benchmark::Mode mode,
                    float ptmin, float ptmax, float etamin, float etamax, 
				 float phimin, float phimax, bool fracHistoFlag) {
  dRMax_                 = dRMax;
  matchCharge_           = matchCharge;
  mode_                  = mode;
  createPFractionHistos_ = fracHistoFlag;
  
  setRange( ptmin, ptmax, etamin, etamax, phimin, phimax );

  candBench_.setParameters(mode_);
  matchCandBench_.setParameters(mode_);

}
//
// -- Create histograms accessing parameters from ParameterSet
//
void PFJetMonitor::setup(const edm::ParameterSet & parameterSet) {
  candBench_.setup(parameterSet);
  matchCandBench_.setup(parameterSet);

  if (createPFractionHistos_ && !histogramBooked_) {
    delta_frac_VS_frac_muon_ = book2D("delta_frac_VS_frac_muon_", 
 "#DeltaFraction_Vs_Fraction(muon)", 100, 0.0, 1.0, 100, -1.0, 1.0);
    delta_frac_VS_frac_photon_ = book2D("delta_frac_VS_frac_photon_", 
 "#DeltaFraction_Vs_Fraction(photon)", 100, 0.0, 1.0, 100, -1.0, 1.0);
    delta_frac_VS_frac_electron_ = book2D("delta_frac_VS_frac_electron_", 
 "#DeltaFraction_Vs_Fraction(electron)", 100, 0.0, 1.0, 100, -1.0, 1.0);
    delta_frac_VS_frac_charged_hadron_ = book2D("delta_frac_VS_frac_charged_hadron_", 
 "#DeltaFraction_Vs_Fraction(charged hadron)", 100, 0.0, 1.0, 100, -1.0, 1.0);
    delta_frac_VS_frac_neutral_hadron_ = book2D("delta_frac_VS_frac_neutral_hadron_", 
 "#DeltaFraction_Vs_Fraction(neutral hadron)", 100, 0.0, 1.0, 100, -1.0, 1.0);
  
    histogramBooked_ = true;
  }

}
//
// -- Create histograms using local parameters
//
void PFJetMonitor::setup() {
  candBench_.setup();
  matchCandBench_.setup();

  if (createPFractionHistos_ && !histogramBooked_) {
    delta_frac_VS_frac_muon_ = book2D("delta_frac_VS_frac_muon_", 
 "#DeltaFraction_Vs_Fraction(muon)", 100, 0.0, 1.0, 100, -1.0, 1.0);
    delta_frac_VS_frac_photon_ = book2D("delta_frac_VS_frac_photon_", 
 "#DeltaFraction_Vs_Fraction(photon)", 100, 0.0, 1.0, 100, -1.0, 1.0);
    delta_frac_VS_frac_electron_ = book2D("delta_frac_VS_frac_electron_", 
 "#DeltaFraction_Vs_Fraction(electron)", 100, 0.0, 1.0, 100, -1.0, 1.0);
    delta_frac_VS_frac_charged_hadron_ = book2D("delta_frac_VS_frac_charged_hadron_", 
 "#DeltaFraction_Vs_Fraction(charged hadron)", 100, 0.0, 1.0, 100, -1.0, 1.0);
    delta_frac_VS_frac_neutral_hadron_ = book2D("delta_frac_VS_frac_neutral_hadron_", 
 "#DeltaFraction_Vs_Fraction(neutral hadron)", 100, 0.0, 1.0, 100, -1.0, 1.0);

    histogramBooked_ = true;
  }

}
//
// -- Set directory to book histograms using ROOT
//

void PFJetMonitor::setDirectory(TDirectory* dir) {
  Benchmark::setDirectory(dir);

  candBench_.setDirectory(dir);
  matchCandBench_.setDirectory(dir);
}
//
// -- fill histograms for a given Jet pair
//
void PFJetMonitor::fillOne(const reco::Jet& jet,
			const reco::Jet& matchedJet) {
  const reco::PFJet* pfJet = dynamic_cast<const reco::PFJet*>(&jet);
  const reco::PFJet* pfMatchedJet = dynamic_cast<const reco::PFJet*>(&matchedJet);
  if (pfJet && pfMatchedJet && createPFractionHistos_) {
    float frac_muon = -99.9;
    float frac_elec = -99.9; 
    float frac_phot = -99.9;
    float frac_ch_had = -99.9;
    float frac_neu_had = -99.9;
 
    if (pfMatchedJet->muonMultiplicity() > 0) frac_muon = (pfJet->muonMultiplicity() - pfMatchedJet->muonMultiplicity())*1.0/pfMatchedJet->muonMultiplicity(); 
    if (pfMatchedJet->chargedHadronMultiplicity() > 0) frac_ch_had = (pfJet->chargedHadronMultiplicity() - pfMatchedJet->chargedHadronMultiplicity())*1.0/pfMatchedJet->chargedHadronMultiplicity(); 
    if (pfMatchedJet->neutralHadronMultiplicity() > 0) frac_neu_had = (pfJet->neutralHadronMultiplicity() - pfMatchedJet->neutralHadronMultiplicity())*1.0/pfMatchedJet->neutralHadronMultiplicity(); 
    if (pfMatchedJet->photonMultiplicity() > 0) frac_phot = (pfJet->photonMultiplicity() - pfMatchedJet->photonMultiplicity())*1.0/pfMatchedJet->photonMultiplicity(); 
    if (pfMatchedJet->electronMultiplicity() > 0) frac_elec = (pfJet->electronMultiplicity() - pfMatchedJet->electronMultiplicity())*1.0/pfMatchedJet->electronMultiplicity(); 

    delta_frac_VS_frac_muon_->Fill(frac_muon);
    delta_frac_VS_frac_electron_->Fill(frac_elec);
    delta_frac_VS_frac_photon_->Fill(frac_phot);
    delta_frac_VS_frac_charged_hadron_->Fill(frac_ch_had);
    delta_frac_VS_frac_neutral_hadron_->Fill(frac_neu_had);
  }
}

