#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: superShape3d

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/SuperShape3DFunc.java

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/



#include "datahelpers.h"



typedef struct
{
	double rho;
	double phi;
	double m1;
	double m2;
	double a1;
	double a2;
	double b1;
	double b2;
	double n1_1;
	double n1_2;
	double n2_1;
	double n2_2;
	double n3_1;
	double n3_2;
	double spiral;
	int toroidmap;
	double _n1n_1;
	double _n1n_2;
	double _m4_1;
	double _m4_2;
	double _an2_1;
	double _an2_2;
	double _bn3_1;
	double _bn3_2;
	double _rho_pi;
	double _phi_pi;

} Variables;

#define APO_VARIABLE_PREFIX "superShape3d_"
#include "plugin.h"

APO_PLUGIN("superShape3d");
APO_VARIABLES(
	VAR_REAL(rho, 9.9),
	VAR_REAL(phi, 2.5),
	VAR_REAL(m1, 6.0),
	VAR_REAL(m2, 3.0),
	VAR_REAL(a1, 1.0),
	VAR_REAL(a2, 1.0),
	VAR_REAL(b1, 1.0),
	VAR_REAL(b2, 1.0),
	VAR_REAL(n1_1, 1.0),
	VAR_REAL(n1_2, 1.0),
	VAR_REAL(n2_1, 1.0),
	VAR_REAL(n2_2, 1.0),
	VAR_REAL(n3_1, 1.0),
	VAR_REAL(n3_2, 1.0),
	VAR_REAL(spiral, 0.0),
	VAR_INTEGER(toroidmap, 0)

);



int PluginVarPrepare(Variation* vp)
{
    VAR(_n1n_1) = (-1.0 / VAR(n1_1));
    VAR(_n1n_2) = (-1.0 / VAR(n1_2));
    VAR(_an2_1) = pow(fabs(1.0 / VAR(a1)), VAR(n2_1));
    VAR(_an2_2) = pow(fabs(1.0 / VAR(a2)), VAR(n2_2));
    VAR(_bn3_1) = pow(fabs(1.0 / VAR(b1)), VAR(n3_1));
    VAR(_bn3_2) = pow(fabs(1.0 / VAR(b2)), VAR(n3_2));
    VAR(_m4_1) = VAR(m1) / 4.0;
    VAR(_m4_2) = VAR(m2) / 4.0;
    VAR(_rho_pi) = VAR(rho) * M_2_PI;
    VAR(_phi_pi) = VAR(phi) * M_2_PI;

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // SuperShape3d by David Young, http://fractal-resources.deviantart.com/gallery/24660058#/d1o8z8x
    double rho1 = GOODRAND_01() * VAR(_rho_pi);
    double phi1 = GOODRAND_01() * VAR(_phi_pi);
    int p = (int) fmod(GOODRAND_0X(INT_MAX), 2);
    if (p == 1) {
      phi1 = (-phi1);
    }
    double sinr = sin(rho1);
    double cosr = cos(rho1);
    double sinp = sin(phi1);
    double cosp = cos(phi1);

    double msinr, mcosr;
    {
      double a = VAR(_m4_1) * rho1;
      msinr = sin(a);
      mcosr = cos(a);
    }
    double msinp, mcosp;
    {
      double a = VAR(_m4_2) * phi1;
      msinp = sin(a);
      mcosp = cos(a);
    }
    double pr1 = VAR(_an2_1) * pow(fabs(mcosr), VAR(n2_1)) + VAR(_bn3_1) * pow(fabs(msinr), VAR(n3_1));
    double pr2 = VAR(_an2_2) * pow(fabs(mcosp), VAR(n2_2)) + VAR(_bn3_2) * pow(fabs(msinp), VAR(n3_2));
    double r1 = pow(pr1, VAR(_n1n_1)) + VAR(spiral) * rho1;
    double r2 = pow(pr2, VAR(_n1n_2));

    if (VAR(toroidmap) == 1) {
      FPx += VVAR * cosr * (r1 + r2 * cosp);
      FPy += VVAR * sinr * (r1 + r2 * cosp);
      FPz += VVAR * r2 * sinp;
    } else {
      FPx += VVAR * r1 * cosr * r2 * cosp;
      FPy += VVAR * r1 * sinr * r2 * cosp;
      FPz += VVAR * r2 * sinp;
    }


    return TRUE;
}





// original java file embedded here:
//
// /*
//   JWildfire - an image and animation processor written in Java 
//   Copyright (C) 1995-2011 Andreas Maschke
// 
//   This is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser 
//   General Public License as published by the Free Software Foundation; either version 2.1 of the 
//   License, or (at your option) any later version.
//  
//   This software is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without 
//   even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
//   Lesser General Public License for more details.
// 
//   You should have received a copy of the GNU Lesser General Public License along with this software; 
//   if not, write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
//   02110-1301 USA, or see the FSF site: http://www.fsf.org.
// */
// package org.jwildfire.create.tina.variation;
// 
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.Tools.FTOI;
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class SuperShape3DFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_RHO = "rho";
//   private static final String PARAM_PHI = "phi";
//   private static final String PARAM_M1 = "m1";
//   private static final String PARAM_M2 = "m2";
//   private static final String PARAM_A1 = "a1";
//   private static final String PARAM_A2 = "a2";
//   private static final String PARAM_B1 = "b1";
//   private static final String PARAM_B2 = "b2";
//   private static final String PARAM_N1_1 = "n1_1";
//   private static final String PARAM_N1_2 = "n1_2";
//   private static final String PARAM_N2_1 = "n2_1";
//   private static final String PARAM_N2_2 = "n2_2";
//   private static final String PARAM_N3_1 = "n3_1";
//   private static final String PARAM_N3_2 = "n3_2";
//   private static final String PARAM_SPIRAL = "spiral";
//   private static final String PARAM_TOROIDMAP = "toroidmap";
//   private static final String[] paramNames = {PARAM_RHO, PARAM_PHI, PARAM_M1, PARAM_M2, PARAM_A1, PARAM_A2, PARAM_B1, PARAM_B2, PARAM_N1_1, PARAM_N1_2, PARAM_N2_1, PARAM_N2_2, PARAM_N3_1, PARAM_N3_2, PARAM_SPIRAL, PARAM_TOROIDMAP};
// 
//   private double rho = 9.9;
//   private double phi = 2.5;
//   private double m1 = 6.0;
//   private double m2 = 3.0;
//   private double a1 = 1.0;
//   private double a2 = 1.0;
//   private double b1 = 1.0;
//   private double b2 = 1.0;
//   private double n1_1 = 1.0;
//   private double n1_2 = 1.0;
//   private double n2_1 = 1.0;
//   private double n2_2 = 1.0;
//   private double n3_1 = 1.0;
//   private double n3_2 = 1.0;
//   private double spiral = 0.0;
//   private int toroidmap = 0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // SuperShape3d by David Young, http://fractal-resources.deviantart.com/gallery/24660058#/d1o8z8x
//     double rho1 = pContext.random() * rho_pi;
//     double phi1 = pContext.random() * phi_pi;
//     int p = (int) fmod(pContext.random(Integer.MAX_VALUE), 2);
//     if (p == 1) {
//       phi1 = (-phi1);
//     }
//     double sinr = sin(rho1);
//     double cosr = cos(rho1);
//     double sinp = sin(phi1);
//     double cosp = cos(phi1);
// 
//     double msinr, mcosr;
//     {
//       double a = m4_1 * rho1;
//       msinr = sin(a);
//       mcosr = cos(a);
//     }
//     double msinp, mcosp;
//     {
//       double a = m4_2 * phi1;
//       msinp = sin(a);
//       mcosp = cos(a);
//     }
//     double pr1 = an2_1 * pow(fabs(mcosr), n2_1) + bn3_1 * pow(fabs(msinr), n3_1);
//     double pr2 = an2_2 * pow(fabs(mcosp), n2_2) + bn3_2 * pow(fabs(msinp), n3_2);
//     double r1 = pow(pr1, n1n_1) + spiral * rho1;
//     double r2 = pow(pr2, n1n_2);
// 
//     if (toroidmap == 1) {
//       pVarTP.x += pAmount * cosr * (r1 + r2 * cosp);
//       pVarTP.y += pAmount * sinr * (r1 + r2 * cosp);
//       pVarTP.z += pAmount * r2 * sinp;
//     } else {
//       pVarTP.x += pAmount * r1 * cosr * r2 * cosp;
//       pVarTP.y += pAmount * r1 * sinr * r2 * cosp;
//       pVarTP.z += pAmount * r2 * sinp;
//     }
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{rho, phi, m1, m2, a1, a2, b1, b2, n1_1, n1_2, n2_1, n2_2, n3_1, n3_2, spiral, toroidmap};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_RHO.equalsIgnoreCase(pName))
//       rho = pValue;
//     else if (PARAM_PHI.equalsIgnoreCase(pName))
//       phi = pValue;
//     else if (PARAM_M1.equalsIgnoreCase(pName))
//       m1 = pValue;
//     else if (PARAM_M2.equalsIgnoreCase(pName))
//       m2 = pValue;
//     else if (PARAM_A1.equalsIgnoreCase(pName))
//       a1 = pValue;
//     else if (PARAM_A2.equalsIgnoreCase(pName))
//       a2 = pValue;
//     else if (PARAM_B1.equalsIgnoreCase(pName))
//       b1 = pValue;
//     else if (PARAM_B2.equalsIgnoreCase(pName))
//       b2 = pValue;
//     else if (PARAM_N1_1.equalsIgnoreCase(pName))
//       n1_1 = pValue;
//     else if (PARAM_N1_2.equalsIgnoreCase(pName))
//       n1_2 = pValue;
//     else if (PARAM_N2_1.equalsIgnoreCase(pName))
//       n2_1 = pValue;
//     else if (PARAM_N2_2.equalsIgnoreCase(pName))
//       n2_2 = pValue;
//     else if (PARAM_N3_1.equalsIgnoreCase(pName))
//       n3_1 = pValue;
//     else if (PARAM_N3_2.equalsIgnoreCase(pName))
//       n3_2 = pValue;
//     else if (PARAM_SPIRAL.equalsIgnoreCase(pName))
//       spiral = pValue;
//     else if (PARAM_TOROIDMAP.equalsIgnoreCase(pName)) {
//       toroidmap = FTOI(pValue);
//       if (toroidmap < 0) {
//         toroidmap = 0;
//       } else if (toroidmap > 1) {
//         toroidmap = 1;
//       }
//     } else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "superShape3d";
//   }
// 
//   private double n1n_1, n1n_2, m4_1, m4_2;
//   private double an2_1, an2_2, bn3_1, bn3_2;
//   private double rho_pi, phi_pi;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     n1n_1 = (-1.0 / n1_1);
//     n1n_2 = (-1.0 / n1_2);
//     an2_1 = pow(fabs(1.0 / a1), n2_1);
//     an2_2 = pow(fabs(1.0 / a2), n2_2);
//     bn3_1 = pow(fabs(1.0 / b1), n3_1);
//     bn3_2 = pow(fabs(1.0 / b2), n3_2);
//     m4_1 = m1 / 4.0;
//     m4_2 = m2 / 4.0;
//     rho_pi = rho * M_2_PI;
//     phi_pi = phi * M_2_PI;
//   }
// 
// }
// 
