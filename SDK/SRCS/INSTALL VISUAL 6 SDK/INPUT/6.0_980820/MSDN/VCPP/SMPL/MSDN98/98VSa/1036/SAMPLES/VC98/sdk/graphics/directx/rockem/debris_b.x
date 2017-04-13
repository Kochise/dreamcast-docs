xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header {
 1;
 0;
 1;
}

Mesh {
 10;
 0.082451;-0.082450;-6.700000;,
 0.082451;0.082451;-6.700000;,
 -0.082451;0.082451;-6.700000;,
 -0.082451;-0.082450;-6.700000;,
 3.349999;-3.350001;-0.000000;,
 3.350000;3.350000;0.000000;,
 -3.349999;3.350001;0.000000;,
 -3.350002;-3.349998;-0.000000;,
 0.000000;0.000000;-6.700000;,
 0.000000;-0.000000;-0.000000;;

 16;
 3;0,8,1;,
 3;1,8,2;,
 3;2,8,3;,
 3;3,8,0;,
 3;0,5,4;,
 3;0,1,5;,
 3;1,6,5;,
 3;1,2,6;,
 3;2,7,6;,
 3;2,3,7;,
 3;3,4,7;,
 3;3,0,4;,
 3;4,5,9;,
 3;5,6,9;,
 3;6,7,9;,
 3;7,4,9;;

 MeshMaterialList {
  1;
  1;
  0;;
  Material {
   0.274510;0.325490;0.905882;1.000000;;
   30.000000;
   0.768627;0.768627;0.768627;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  26;
  0.000000;0.000000;-1.000000;,
  0.898808;-0.000000;-0.438343;,
  -0.000000;-0.898808;-0.438343;,
  0.000000;0.000000;-1.000000;,
  0.898808;-0.000000;-0.438343;,
  0.000000;0.898808;-0.438343;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.898808;-0.438343;,
  -0.898808;0.000000;-0.438343;,
  0.000000;0.000000;-1.000000;,
  -0.898808;0.000000;-0.438343;,
  -0.000000;-0.898808;-0.438343;,
  0.898808;-0.000000;-0.438343;,
  -0.000000;-0.898808;-0.438343;,
  0.000000;-0.000000;1.000000;,
  0.898808;-0.000000;-0.438343;,
  0.000000;0.898808;-0.438343;,
  0.000000;-0.000000;1.000000;,
  0.000000;0.898808;-0.438343;,
  -0.898808;0.000000;-0.438343;,
  0.000000;-0.000000;1.000000;,
  -0.898808;0.000000;-0.438343;,
  -0.000000;-0.898808;-0.438343;,
  0.000000;-0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;-0.000000;1.000000;;

  16;
  3;0,24,3;,
  3;3,24,6;,
  3;6,24,9;,
  3;9,24,0;,
  3;1,15,12;,
  3;1,4,15;,
  3;5,18,16;,
  3;5,7,18;,
  3;8,21,19;,
  3;8,10,21;,
  3;11,13,22;,
  3;11,2,13;,
  3;14,17,25;,
  3;17,20,25;,
  3;20,23,25;,
  3;23,14,25;;
 }
 MeshTextureCoords {
  10;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
