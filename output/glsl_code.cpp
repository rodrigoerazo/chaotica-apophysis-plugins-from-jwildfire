#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: glsl_code

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/GLSLBaseFunc.java

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
	double _zoom = 4.0;
	int _gradient = 1;

} Variables;

#define APO_VARIABLE_PREFIX "glsl_code_"
#include "plugin.h"

APO_PLUGIN("glsl_code");
APO_VARIABLES(


);


void initOnce (Variation* vp, Layer pLayer, XForm pXForm, double pAmount) {

    super.initOnce(vp, pLayer, pXForm, VVAR);

}

void compile (Variation* vp) {


    try {
      cf_runner = glslFuncRunner.compile(vp, header0 + AddParams() + code_func);
    } catch (Throwable ex) {
      System.out.println("##############################################################");
      System.out.println(ex.getMessage());
      System.out.println("##############################################################");
      System.out.println(code_func);
      System.out.println("##############################################################");
    }
}

void validate (Variation* vp) {


    try {
      if (code_func != null) {
        glslFuncRunner.compile(vp, header0 + AddParams() + code_func);
      }
    } catch (Throwable ex) {
      throw new RuntimeException(ex);
    }
}

boolean dynamicParameterExpansion (Variation* vp) {

    return true;
}

boolean dynamicParameterExpansion (Variation* vp, String pName) {

    // preset_id doesn't really expand parameters, but it changes them; this will make them refresh
    return true;
}

void setRessource (Variation* vp, String pName, byte[] pValue) {

    if (RESSOURCE_CODE.equalsIgnoreCase(pName)) {
      code_func = pValue != null ? new String(pValue) : "";
    } else
      throw new IllegalArgumentException(pName);
}


int PluginVarPrepare(Variation* vp)
{
   VAR(_resolutionX) = 1000000;
   VAR(_zoom) = 4.0;
   VAR(_gradient) = 1;

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
// import js.glsl.glslFuncRunner;
// import js.glsl.vec3;
// import org.jwildfire.base.Tools;
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// 
// public class GLSLBaseFunc extends VariationFunc {
// 
//   /*
//    * Variation : glsl_code
//    *
//    * Autor: Jesus Sosa
//    * Date: October 31, 2018
//    * Reference https://www.interactiveshaderformat.com/sketches/3403#
//    */
// 
// 
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_RESOLUTIONX = "ResolutionX";
//   private static final String PARAM_RESOLUTIONY = "ResolutionY";
// 
//   private static final String PARAM_ZOOM = "zoom";
//   private static final String PARAM_GRADIENT = "Gradient";
// 
// 
//   private static final String[] paramNames = {PARAM_RESOLUTIONX, PARAM_RESOLUTIONY, PARAM_ZOOM, PARAM_GRADIENT};
// 
// 
//   private static final String RESSOURCE_CODE = "code";
//   private static final String[] ressourceNames = {RESSOURCE_CODE};
// 
// 
//   int resolutionX = 1000000;
//   int resolutionY = resolutionX;
// 
//   double zoom = 4.0;
// 
//   int gradient = 1;
// 
//   glslFuncRunner cf_runner = null;
// 
//   String header0 = "import js.glsl.vec2;\n" +
//           "import js.glsl.vec3;\n" +
//           "import js.glsl.vec4;\n" +
//           "import js.glsl.mat2;\n" +
//           "import js.glsl.mat3;\n" +
//           "import js.glsl.mat4;\n";
// 
//   String code_func = "public vec3 getRGBColor(int i,int j)\n" +
//           "{\n" +
//           "  double xt=(double)i +0.5;\n" +
//           "  double yt=(double)j +0.5;\n" +
//           "  vec2 st=new vec2(2.0*xt/resolutionX-1.0,2.0*yt/resolutionY-1.0);\n" +
//           "  vec3 color=new vec3(0.0);\n" +
// 
//           "  vec2 c = st.multiply(zoom).minus(new vec2(0.5,0.0));\n" +
//           "  color = fractal(c);\n" +
//           "  return color;\n" +
//           "}\n";
// 
// 
//   @Override
//   public void initOnce(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     super.initOnce(pContext, pLayer, pXForm, pAmount);
// 
//   }
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     compile();
//   }
// 
//   public String AddParams() {
//     String sReturn = "int resolutionX=" + resolutionX + ";\n" +
//             "int resolutionY=" + resolutionY + ";\n" +
//             "double zoom=" + zoom + ";\n";
// 
//     return sReturn;
//   }
// 
//   public void compile() {
// 
//     try {
//       cf_runner = glslFuncRunner.compile(header0 + AddParams() + code_func);
//     } catch (Throwable ex) {
//       System.out.println("##############################################################");
//       System.out.println(ex.getMessage());
//       System.out.println("##############################################################");
//       System.out.println(code_func);
//       System.out.println("##############################################################");
//     }
//   }
// 
//   @Override
//   public void validate() {
// 
//     try {
//       if (code_func != null) {
//         glslFuncRunner.compile(header0 + AddParams() + code_func);
//       }
//     } catch (Throwable ex) {
//       throw new RuntimeException(ex);
//     }
//   }
// 
//   public int[] dbl2int(vec3 theColor) {
//     int[] color = new int[3];
// 
//     int col = (int) (256D * theColor.x);
//     if (col > 255)
//       col = 255;
//     color[0] = col;
//     col = (int) (256D * theColor.y);
//     if (col > 255)
//       col = 255;
//     color[1] = col;
//     col = (int) (256D * theColor.z);
//     if (col > 255)
//       col = 255;
//     color[2] = col;
//     return color;
//   }
// 
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
// 
// 
//     int i = (int) (pContext.random() * resolutionX);
//     int j = (int) (pContext.random() * resolutionY);
// 
//     vec3 color = new vec3(0.0);
// 
//     color = cf_runner.getRGBColor(i, j);
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
//     return "glsl_code";
//   }
// 
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   public Object[] getParameterValues() { //re_min,re_max,im_min,im_max,
//     return new Object[]{resolutionX, resolutionY, zoom, gradient};
//   }
// 
//   public void setParameter(String pName, double pValue) {
//     if (pName.equalsIgnoreCase(PARAM_RESOLUTIONX)) {
//       resolutionX = (int) Tools.limitValue(pValue, 100, 1000000);
//     } else if (pName.equalsIgnoreCase(PARAM_RESOLUTIONY)) {
//       resolutionY = (int) Tools.limitValue(pValue, 100, 1000000);
//     } else if (pName.equalsIgnoreCase(PARAM_ZOOM)) {
//       zoom = Tools.limitValue(pValue, 0, 100);
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
//   @Override
//   public String[] getRessourceNames() {
//     return ressourceNames;
//   }
// 
// 
//   @Override
//   public byte[][] getRessourceValues() {
//     return new byte[][]{(code_func != null ? code_func.getBytes() : null)};
//   }
// 
//   @Override
//   public RessourceType getRessourceType(String pName) {
//     if (pName.equals(RESSOURCE_CODE)) {
//       return RessourceType.JAVA_CODE;
//     } else {
//       return super.getRessourceType(pName);
//     }
//   }
// 
//   @Override
//   public void setRessource(String pName, byte[] pValue) {
//     if (RESSOURCE_CODE.equalsIgnoreCase(pName)) {
//       code_func = pValue != null ? new String(pValue) : "";
//     } else
//       throw new IllegalArgumentException(pName);
//   }
// }
// 
// 
