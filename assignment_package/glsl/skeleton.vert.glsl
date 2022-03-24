#version 150


uniform mat4 u_Model;       //The matrix that defines the transformation of the
                            //object we're rendering. In this assignment,
                            //this will be the result of traversing your scene graph.

uniform mat4 u_ModelInvTr;  //The inverse transpose of the model matrix.
                            //This allows us to transform the object's normals properly
                            //if the object has been non-uniformly scaled.

uniform mat4 u_ViewProj;    //The matrix that defines the camera's transformation.
                            //We've written a static matrix for you to use for HW2,
                            //but in HW3 you'll have to generate one yourself

uniform mat4 u_TransMats[100]; // A uniform array of matrices (or dual quaternions

uniform mat4 u_BindMats[100]; // A uniform array of matrices that each describe the bind matrix of a particular joint.

in vec4 vs_Pos;             // The array of vertex positions passed to the shader
in vec4 vs_Nor;             // The array of vertex normals passed to the shader
in vec4 vs_Col;             // The array of vertex colors passed to the shader.

in vec2 weights;
in ivec2 joint_IDs;

out vec4 fs_Nor;            // The array of normals that has been transformed by u_ModelInvTr. This is implicitly passed to the fragment shader.
out vec4 fs_Col;            // The color of each vertex. This is implicitly passed to the fragment shader.


void main()
{
    fs_Col = vs_Col;

    vec4 pos1 = u_TransMats[joint_IDs[0]] *
                 u_BindMats[joint_IDs[0]] * vs_Pos;
    vec4 pos2 = u_TransMats[joint_IDs[1]] *
                 u_BindMats[joint_IDs[1]] * vs_Pos;

    vec4 pos = weights[0] * pos1 + weights[1] * pos2;
    vec4 modelposition = u_Model * pos;


    gl_Position = u_ViewProj * modelposition;// gl_Position is a built-in variable of OpenGL which is used to render the final positions
                                             // of the geometry's vertices
}
