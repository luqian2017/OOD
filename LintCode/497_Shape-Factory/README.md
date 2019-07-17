497. Shape Factory
中文English
Factory is a design pattern in common usage. Implement a ShapeFactory that can generate correct shape.

You can assume that we have only three different shapes: Triangle, Square and Rectangle.

Example
Example 1:

Input:
ShapeFactory sf = new ShapeFactory();
Shape shape = sf.getShape("Square");
shape.draw();
Output:
  ----
 |    |
 |    |
  ----
Example 2:

Input:
ShapeFactory sf = new ShapeFactory();
shape = sf.getShape("Triangle");
shape.draw();
Output:
   /\
  /  \
 /____\
Example 3:


Input:
ShapeFactory sf = new ShapeFactory();
shape = sf.getShape("Rectangle");
shape.draw();
Output:
  ----
 |    |
  ----
