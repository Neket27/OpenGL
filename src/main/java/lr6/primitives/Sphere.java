package lr6.primitives;

import org.joml.Vector3f;

public class Sphere {
   private float radius;
   private int slices;
   private int stacks;
   private int vertexCount;
   private float[] vertices;
   private float[] textureCoords;
    private float[] normalsArray;
   private int[] indices;



    public Sphere(float radius, int slices, int stacks) {
        this.radius = radius;
        this.slices = slices;
        this.stacks = stacks;
        createSphere(radius,slices,stacks);
    }

    private void createSphere(float radius, int slices, int stacks) {
        vertexCount = (slices + 1) * (stacks + 1);
        vertices = new float[vertexCount * 3];
        textureCoords = new float[vertexCount * 2];
        normalsArray = new float[vertexCount * 3]; // Нормали
        indices = new int[slices * stacks * 6];

        int vertexIndex = 0;
        int textureIndex = 0;
        int normalIndex = 0;
        int index = 0;

        for (int stack = 0; stack <= stacks; stack++) {
            float stackAngle = (float) Math.PI / 2 - (float) stack * (float) Math.PI / stacks;
            float y = radius * (float) Math.sin(stackAngle);
            float r = radius * (float) Math.cos(stackAngle);

            for (int slice = 0; slice <= slices; slice++) {
                float sliceAngle = (float) slice * 2 * (float) Math.PI / slices;
                float x = r * (float) Math.cos(sliceAngle);
                float z = r * (float) Math.sin(sliceAngle);

                vertices[vertexIndex++] = x;
                vertices[vertexIndex++] = y;
                vertices[vertexIndex++] = z;

                textureCoords[textureIndex++] = (float) slice / slices;
                textureCoords[textureIndex++] = (float) stack / stacks;

                Vector3f vertex = new Vector3f(x, y, z).normalize();
                normalsArray[normalIndex++] = vertex.x;
                normalsArray[normalIndex++] = vertex.y;
                normalsArray[normalIndex++] = vertex.z;

                if (stack < stacks && slice < slices) {
                    int next = slice + 1;
                    int nextStack = stack + 1;

                    indices[index++] = slice + stack * (slices + 1);
                    indices[index++] = next + stack * (slices + 1);
                    indices[index++] = slice + nextStack * (slices + 1);

                    indices[index++] = next + stack * (slices + 1);
                    indices[index++] = next + nextStack * (slices + 1);
                    indices[index++] = slice + nextStack * (slices + 1);
                }
            }
        }

        // У вас есть массивы vertices, textureCoords, normalsArray и indices для рисования сферы.
    }

    public float getRadius() {
        return radius;
    }

    public int getSlices() {
        return slices;
    }

    public int getStacks() {
        return stacks;
    }

    public int getVertexCount() {
        return vertexCount;
    }

    public float[] getVertices() {
        return vertices;
    }

    public float[] getTextureCoords() {
        return textureCoords;
    }

    public int[] getIndices() {
        return indices;
    }

    public void setRadius(float radius) {
        this.radius = radius;
    }

    public void setSlices(int slices) {
        this.slices = slices;
    }

    public void setStacks(int stacks) {
        this.stacks = stacks;
    }

    public void setVertexCount(int vertexCount) {
        this.vertexCount = vertexCount;
    }

    public void setVertices(float[] vertices) {
        this.vertices = vertices;
    }

    public void setTextureCoords(float[] textureCoords) {
        this.textureCoords = textureCoords;
    }

    public void setIndices(int[] indices) {
        this.indices = indices;
    }

    public float[] getNormalsArray() {
        return normalsArray;
    }

    public void setNormalsArray(float[] normalsArray) {
        this.normalsArray = normalsArray;
    }
}
