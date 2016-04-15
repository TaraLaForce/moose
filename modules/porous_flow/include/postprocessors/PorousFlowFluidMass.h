/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/


#ifndef POROUSFLOWFLUIDMASS_H
#define POROUSFLOWFLUIDMASS_H

#include "ElementIntegralVariablePostprocessor.h"
#include "PorousFlowDictator.h"

// Forward Declarations
class PorousFlowFluidMass;

template<>
InputParameters validParams<PorousFlowFluidMass>();

/**
 * Postprocessor produces the fluid-component mass in a region
 */
class PorousFlowFluidMass: public ElementIntegralVariablePostprocessor
{
public:

  PorousFlowFluidMass(const InputParameters & parameters);

protected:
  virtual Real computeQpIntegral();

  unsigned int _component_index;

  /// holds info on the Richards variables
  const PorousFlowDictator & _porflow_name_UO;

  const MaterialProperty<Real> & _porosity;

  const MaterialProperty<std::vector<Real> > & _fluid_density;

  const MaterialProperty<std::vector<Real> > & _fluid_saturation;

  const MaterialProperty<std::vector<std::vector<Real> > > & _mass_frac;

};

#endif //POROUSFLOWFLUIDMASS_H
