#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: glsl_fractaldots

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/GLSLFractalDotsFunc.java

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
	int _resolutionX = 1000000;
	int _resolutionY; // resolutionX
	int _iterations = 9;
	double _dotsize = 400.0;
	double _maxiterations = 10;
	double _complexity = 0.001245675;
	double _pattern = 2.5;
	double _spacing = 12.0;
	double _rotate1 = 1.5;
	double _rotate2 = 64.0;
	double _zoom = 64.0;
	int _gradient;
	double _circleSize; // dotsize / (3.0 * Math.pow(2.0
	double _(double) maxiterations));

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "glsl_fractaldots_"
#include "plugin.h"

APO_PLUGIN("glsl_fractaldots");
APO_VARIABLES(

);


boolean dynamicParameterExpansion (Variation* vp) {

    return true;
}

boolean dynamicParameterExpansion (Variation* vp, String pName) {

    // preset_id doesn't really expand parameters, but it changes them; this will make them refresh
    return true;
}


int PluginVarPrepare(Variation* vp)
{
   VAR(_resolutionX) = 1000000;
   VAR(_iterations) = 9;
   VAR(_dotsize) = 400.0;
   VAR(_maxiterations) = 10;
   VAR(_complexity) = 0.001245675;
   VAR(_pattern) = 2.5;
   VAR(_spacing) = 12.0;
   VAR(_rotate1) = 1.5;
   VAR(_rotate2) = 64.0;
   VAR(_zoom) = 64.0;

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{


    return TRUE;
}





// original java file embedded here:
//
// package org.jwildfire.create.tina.variation;
// 
// import js.glsl.G;
// import js.glsl.vec2;
// import js.glsl.vec3;
// import org.jwildfire.base.Tools;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// public class GLSLFractalDotsFunc extends GLSLFunc {
// 
//   /*
//    * Variation : glsl_fractaldots
//    * Autor: Jesus Sosa
//    * Date: October 31, 2018
//    * Reference
//    */
// 
// 
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_RESOLUTIONX = "Density Pixels";
//   private static final String PARAM_ITERATIONS = "iterations";
//   private static final String PARAM_DOTSIZE = "DotSize";
//   private static final String PARAM_MAXITER = "MaxIterations";
//   private static final String PARAM_COMPLEXITY = "complexity";
//   private static final String PARAM_PATTERN = "pattern";
//   private static final String PARAM_SPACING = "spacing";
//   private static final String PARAM_ROTATE1 = "rotate1";
//   private static final String PARAM_ROTATE2 = "rotate2";
//   private static final String PARAM_ZOOM = "zoom";
//   private static final String PARAM_GRADIENT = "Gradient";
// 
//   int resolutionX = 1000000;
//   int resolutionY = resolutionX;
//   int iterations = 9;
//   double dotsize = 400.;
//   double maxiterations = 10;
//   double complexity = 0.001245675;
//   double pattern = 2.5;
//   double spacing = 12.;
//   double rotate1 = 1.5;
//   double rotate2 = 64.;
//   double zoom = 64.;
// 
// 
//   int gradient = 0;
// 
//   private static final String[] paramNames = {PARAM_RESOLUTIONX, PARAM_ITERATIONS, PARAM_DOTSIZE, PARAM_MAXITER, PARAM_COMPLEXITY, PARAM_PATTERN, PARAM_SPACING, PARAM_ROTATE1, PARAM_ROTATE2, PARAM_ZOOM, PARAM_GRADIENT};
// 
// 
//   public vec2 rot(vec2 uv, double a) {
// 
//     return new vec2(uv.x * G.cos(a) - uv.y * G.sin(a), uv.y * G.cos(a) + uv.x * G.sin(a));
// 
//   }
// 
//   double circleSize = dotsize / (3.0 * Math.pow(2.0, (double) maxiterations));
// 
//   public vec3 getRGBColor(int xp, int yp) {
//     double x = (double) xp + 0.5;
//     double y = (double) yp + 0.5;
//     vec2 uv = new vec2(x / resolutionX - .5, y / resolutionY - .5);
// 
//     vec3 col = new vec3(0.0);
//     //global rotation and zoom
//     uv = rot(uv, rotate1);
//     uv = uv.multiply(zoom);
// 
// 
//     //mirror, rotate and scale
//     double s = spacing;
//     for (int i = 0; i < maxiterations; i++) {
//       //uv=floor(abs(uv)-s);
//       uv = G.abs(uv).minus(s);
//       uv = uv.minus(complexity);
//       uv = rot(uv, rotate2);
//       s = s / pattern;
//       if (iterations < i)
//         break;
//     }
// 
//     //draw a circle
//     double c = G.length(uv) > circleSize ? 0.0 : 1.0;
//     return new vec3(c);
//   }
// 
// 
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
// 
// 
//     int i = (int) (pContext.random() * resolutionX);
//     int j = (int) (pContext.random() * resolutionY);
// 
//     vec3 color = new vec3(0.0);
// 
//     color = getRGBColor(i, j);
// 
//     if (gradient == 0) {
//       int[] tcolor = new int[3];
//       tcolor = dbl2int(color);
// 
//       pVarTP.rgbColor = true;
//       ;
//       pVarTP.redColor = tcolor[0];
//       pVarTP.greenColor = tcolor[1];
//       pVarTP.blueColor = tcolor[2];
// 
//     } else {
//       //	pVarTP.color=color.r;
//       pVarTP.color = color.r * color.g;
//       //	pVarTP.color=color.r*color.g*color.b;
//     }
//     pVarTP.x += pAmount * ((double) (i) / resolutionX - 0.5);
//     pVarTP.y += pAmount * ((double) (j) / resolutionY - 0.5);
// 
//   }
// 
// 
//   public String getName() {
//     return "glsl_fractaldots";
//   }
// 
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
// 
//   public Object[] getParameterValues() { //re_min,re_max,im_min,im_max,
//     return new Object[]{resolutionX, iterations, dotsize, maxiterations, complexity, pattern, spacing, rotate1, rotate2, zoom, gradient};
//   }
// 
//   public void setParameter(String pName, double pValue) {
//     if (pName.equalsIgnoreCase(PARAM_RESOLUTIONX)) {
//       resolutionX = (int) Tools.limitValue(pValue, 100, 10000000);
//     } else if (pName.equalsIgnoreCase(PARAM_ITERATIONS)) {
//       iterations = (int) Tools.limitValue(pValue, 1, 100);
//     } else if (pName.equalsIgnoreCase(PARAM_DOTSIZE)) {
//       dotsize = pValue;
//       ;
//     } else if (pName.equalsIgnoreCase(PARAM_MAXITER)) {
//       maxiterations = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_COMPLEXITY)) { // 0.0- 2*Math.PI radians
//       complexity = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_PATTERN)) {
//       pattern = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_SPACING)) {
//       spacing = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_ROTATE1)) {
//       rotate1 = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_ROTATE2)) {
//       rotate2 = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_ZOOM)) {
//       zoom = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_GRADIENT)) {
//       gradient = (int) Tools.limitValue(pValue, 0, 1);
//     } else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public boolean dynamicParameterExpansion() {
//     return true;
//   }
// 
//   @Override
//   public boolean dynamicParameterExpansion(String pName) {
//     // preset_id doesn't really expand parameters, but it changes them; this will make them refresh
//     return true;
//   }
// 
// }
// 
// 
