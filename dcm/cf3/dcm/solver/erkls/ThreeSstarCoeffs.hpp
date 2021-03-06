// Copyright (C) 2010-2013 von Karman Institute for Fluid Dynamics, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.

/// @file ThreeSstarCoeffs.hpp
/// @author Willem Deconinck
///
/// This file defines a Butcher Tableau component

#ifndef cf3_dcm_solver_erkls_ThreeSstarCoeffs_hpp
#define cf3_dcm_solver_erkls_ThreeSstarCoeffs_hpp

#include "cf3/dcm/solver/erkls/LibERKLS.hpp"

namespace cf3 {
namespace dcm {
namespace solver {  
namespace erkls {

////////////////////////////////////////////////////////////////////////////////

/// @brief Component to hold a Butcher tableau, used in Runge-Kutta integration methods.
/// @author Willem Deconinck
///
/// This component is configurable with a vector of coefficients "alpha", and "beta",
/// "gamma" and an informative option "order", describing the order of the RK method,
/// using these coefficients.
/// The coefficients "c" are deduced from the coefficients "a",
/// as the coefficients "c" are always the summation of the corresponding row
/// of coefficients "a".
class dcm_solver_erkls_API ThreeSstarCoeffs : public common::Component
{
public:

  /// @brief Coefficients from the Butcher tableau
  struct Coefficients
  {
    Coefficients() : cfl(0.) {}
    std::vector<Real> delta;   ///< coefficients "a"
    std::vector<Real> beta;    ///< coefficients "a"
    std::vector<Real> gamma1;  ///< coefficients "b"
    std::vector<Real> gamma2;  ///< coefficients "c"
    std::vector<Real> gamma3;  ///< coefficients "c"
    std::vector<Real> c;       ///< coefficients "c"

    Uint order;      ///< order of the table
    Uint nb_stages;  ///< number of stages of the RK method
    Real cfl;        ///< CFL number. This is only a guidance.
  };

public:

  /// @brief Type name
  static std::string type_name() { return "ThreeSstarCoeffs"; }

  /// @brief Constructor
  ThreeSstarCoeffs(const std::string& name);

  /// @brief Configure the internal coefficients through a given Coefficients object
  void set (const Coefficients& coeffs);

  // Coefficient access
  /// @brief Access to element of the "delta" coefficients
  const Real& delta(const Uint i) const { return m_coeffs.delta[i]; }

  /// @brief Access to element of the "beta" coefficients
  const Real& beta(const Uint i) const  { return m_coeffs.beta[i]; }

  /// @brief Access to element of the "gamma" coefficients
  const Real& gamma1(const Uint i) const { return m_coeffs.gamma1[i]; }

  /// @brief Access to element of the "gamma" coefficients
  const Real& gamma2(const Uint i) const { return m_coeffs.gamma2[i]; }
  
  /// @brief Access to element of the "gamma" coefficients
  const Real& gamma3(const Uint i) const { return m_coeffs.gamma3[i]; }
  
  /// @brief Access to element of the "gamma" coefficients
  const Real& c(const Uint i) const { return m_coeffs.c[i]; }
  
  /// @brief Number of stages
  Uint nb_stages() const { return m_coeffs.nb_stages; }

  /// @brief Order
  Uint order() const { return m_coeffs.order; }

  /// @brief Access to stable cfl number
  const Real& cfl() const { return m_coeffs.cfl; }

  /// @brief Check if Butcher tableau is consistent, and throw error if not.
  bool check_throw() const;

  /// @brief String representation of the Butcher tableau:
  std::string str() const;
  
  private: // functions
  
  void configure_nb_stages();
  
private: // data

  Coefficients m_coeffs; ///< Internal coefficients storage

};

////////////////////////////////////////////////////////////////////////////////

} // erkls
} // solver
} // dcm
} // cf3

#endif // cf3_dcm_solver_explicit_ThreeSstarCoeffs_hpp
