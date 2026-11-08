<h1>cpp-matrix-vector-library</h1>
<p>Lightweight, portable dynamic linear algebra library in C providing memory-managed vector and matrix operations, functional transformations, and file serialization</p>

<h2>Project description</h2>
<p>This project implements an efficient, dynamic linear algebra engine in pure C with zero external runtime dependencies:</p>
<ol>
  <li>Encapsulates contiguous dynamic 1D vector and 2D matrix arrays with explicit dimensional tracking (<code>SVector</code>, <code>SMatrix</code>).</li>
  <li>Provides memory-safe constructor/destructor pairs with <code>calloc</code> zero-initialization and clean pointer invalidation.</li>
  <li>Supports file-based streaming serialization (deserializing structured vectors from plain-text definitions).</li>
  <li>Implements functional procedural initialization via function pointers (e.g., $f(x) = x^2$).</li>
  <li>Executes linear algebra routines: vector addition, dot products, scalar scaling, identity matrix synthesis, and matrix-matrix / matrix-vector multiplications.</li>
</ol>

<h2>Project files</h2>
<table>
  <tr>
    <th colspan="2">cpp-matrix-vector-library</th>
  </tr>
  <tr>
    <td>include/SMatrix.h</td>
    <td>Type definitions for contiguous 1D dynamic vectors and 2D dynamic matrices</td>
  </tr>
  <tr>
    <td>include/Matrix.h</td>
    <td>Public API declarations supporting both C and C++ linkage (<code>extern "C"</code>)</td>
  </tr>
  <tr>
    <td>src/Matrix.c</td>
    <td>Implementation of memory allocation, mathematical operators, and file I/O</td>
  </tr>
  <tr>
    <td>src/main.c</td>
    <td>Client demonstration verifying vector creation, serialization, and matrix multiplications</td>
  </tr>
  <tr>
    <td>CMakeLists.txt</td>
    <td>Build configuration compiling a shared library target alongside an executable test runner</td>
  </tr>
</table>

<h2>Installation and launch</h2>
<ol>
  <b>
    <li>
      <dl>
        <dt>Clone repository &amp; compile</dt>
        <dd><code>git clone https://github.com/Kyoryuu-lab/cpp-matrix-vector-library.git</code></dd>
        <dd><code>cd cpp-matrix-vector-library &amp;&amp; cmake -B build &amp;&amp; cmake --build build</code></dd>
      </dl>
    </li>
  </b>
  <b>
    <li>
      <dl>
        <dt>Run test suite</dt>
        <dd><code>./build/matrix_test</code></dd>
      </dl>
    </li>
  </b>
</ol>
