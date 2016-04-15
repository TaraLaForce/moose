/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/


#ifndef POROUSFLOWMATERIALRELATIVEPERMEABILITYCONST_H
#define POROUSFLOWMATERIALRELATIVEPERMEABILITYCONST_H

#include "DerivativeMaterialInterface.h"
#include "Material.h"

#include "PorousFlowDictator.h"

//Forward Declarations
class PorousFlowMaterialRelativePermeabilityConst;

template<>
InputParameters validParams<PorousFlowMaterialRelativePermeabilityConst>();

/**
 * Returns a constant relative permeability (1.0)
 */
class PorousFlowMaterialRelativePermeabilityConst : public DerivativeMaterialInterface<Material>
{
public:
  PorousFlowMaterialRelativePermeabilityConst(const InputParameters & parameters);

protected:

  virtual void computeQpProperties();

  /// The variable names UserObject for the PorousFlow variables
  const PorousFlowDictator & _dictator_UO;
  /// Phase number of fluid that this relative permeability relates to
  const unsigned int _phase_num;
  /// Name of (dummy) saturation primary variable
  VariableName _saturation_variable_name;
  /// Relative permeability material property
  MaterialProperty<Real> & _relative_permeability;
  /// Derivative of relative permeability wrt phase saturation
  MaterialProperty<Real> & _drelative_permeability_ds;
};

#endif //POROUSFLOWMATERIALRELATIVEPERMEABILITYCONST_H
