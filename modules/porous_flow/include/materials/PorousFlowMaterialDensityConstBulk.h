/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/


#ifndef PORFLOWMATERIALDENSITYCONSTBULK_H
#define PORFLOWMATERIALDENSITYCONSTBULK_H

#include "DerivativeMaterialInterface.h"
#include "Material.h"

#include "PorousFlowDictator.h"

//Forward Declarations
class PorousFlowMaterialDensityConstBulk;

template<>
InputParameters validParams<PorousFlowMaterialDensityConstBulk>();

/**
 * Material designed to calculate fluid density
 * from porepressure, assuming constant bulk modulus
 * for the fluid.
 */
class PorousFlowMaterialDensityConstBulk : public DerivativeMaterialInterface<Material>
{
public:
  PorousFlowMaterialDensityConstBulk(const InputParameters & parameters);

protected:

  /// density at zero porepressure
  const Real _dens0;

  /// constant bulk modulus
  const Real _bulk;

  /// phase number of fluid that we're dealing with
  const unsigned int _phase_num;

  /// The variable names UserObject for the Porous-Flow variables
  const PorousFlowDictator & _porflow_name_UO;

  /// nodal porepressure of each phase
  const MaterialProperty<std::vector<Real> > & _porepressure;

  /// d(nodal porepressure)/d(PorousFlow variable)
  const MaterialProperty<std::vector<std::vector<Real> > > & _dporepressure_dvar;

  /// computed nodal density of the phase
  MaterialProperty<Real> & _density;

  /// old value of nodal density of the phase
  MaterialProperty<Real> & _density_old;

  /// d(nodal density)/d(PorousFlow variable)
  MaterialProperty<std::vector<Real> > & _ddensity_dvar;

  /// quadpoint porepressure of each phase
  const MaterialProperty<std::vector<Real> > & _porepressure_qp;

  /// d(quadpoint porepressure)/d(PorousFlow variable)
  const MaterialProperty<std::vector<std::vector<Real> > > & _dporepressure_qp_dvar;

  /// computed quadpoint density of the phase
  MaterialProperty<Real> & _density_qp;

  /// d(quadpoint density)/d(PorousFlow variable)
  MaterialProperty<std::vector<Real> > & _ddensity_qp_dvar;

  virtual void initQpStatefulProperties();
  virtual void computeQpProperties();
};

#endif //PORFLOWMATERIALDENSITYCONSTBULK_H