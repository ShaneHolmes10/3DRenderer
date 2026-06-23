
# Forms

The forms directory contains the code responsible for the scene-tree as well as different renderable objects. 

## Mesh

The foundational object of any rendering system are the triangles. To represent a triangle you need 3 vertices. To build more complex geometries we represent them as composites of several triangles. It would be inefficient to represent each triangle with it's own private set of vertices, because most triangles in a geometry actually share vertices. So for a mesh structure the mesh is comprised of a list of vertices, and another list of faces. The faces list represents groupings of 3 vertices from the vertex list. 

A Vertex3 object is used to store the structure of a vertex. This is basically an object that holds a 3D vector in space, so something like this: 

`v_0 = {300, 200, 400}`

The vertices list would be a list of these vertices:

`[v_0, v_1, v_2, v_3, v_4, v_5, v_6, v_7, v_8]`

A face is just 3 integers. The integers represent the index of the vertex in a vertex list. This is the industry standard. 

`{0, 3, 4}`

The faces list would be something like:

`[ {0, 3, 4}, {5, 7, 8}, {2, 5, 6}, {6, 7, 8} ]`

### Why do faces store integers?

Currently the face stores integers that represent the index of vertices of the vertex list. This might seem a little odd, why not just store the references so the vertices? 

For some background this is how a C++ vector list works. It's essentially a dynamic array, so it's initialized with some fix size and elements can be added and removed. The control structure of this vector list is in the stack, but the content lives in the dynamic heap. So for the vertex list it looks something like this: 

```plaintext
[ Stack ]                                    [ Heap ]

+---------------+---------------+---------------+       +------------------------+------------------------+-----
|   Vertex3*    |     size      |   capacity    |--+--> |       Vertex3 #0       |       Vertex3 #1       | ...
|    8 bytes    |    8 bytes    |    8 bytes    |  |    +------------+-----------+------------+-----------+-----
+---------------+---------------+---------------+  |    |  position  |   color   |  position  |   color   | ...
       vector object (24 bytes)                    |    |  12 bytes  |  12 bytes |  12 bytes  |  12 bytes | ...
                                                   |    +------------+-----------+------------+-----------+-----
                                                   |
                                                  ptr

```

When a new vertex is added, the heap array may run out of capacity. When this happens the vector allocates a new, larger block of memory on the heap, copies all the vertices into it, and frees the old block. Any pointer or reference into the old block is now pointing at freed memory — a dangling pointer — which causes crashes or silent corruption.

An integer index avoids this entirely. The number 2 doesn't store a memory address, it just says "position 2". When you need the actual vertex you look it up fresh with vertices[face.v1], which always goes through the vector's current pointer to wherever the data lives now. No matter how many times the vector has reallocated, the index remains valid.