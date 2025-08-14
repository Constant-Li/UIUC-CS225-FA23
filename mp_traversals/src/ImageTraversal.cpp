#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Point.h"

#include "ImageTraversal.h"

namespace Traversals {
  /**
  * Calculates a metric for the difference between two pixels, used to
  * calculate if a pixel is within a tolerance.
  *
  * @param p1 First pixel
  * @param p2 Second pixel
  * @return the difference between two HSLAPixels
  */
  double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
    double h = fabs(p1.h - p2.h);
    double s = p1.s - p2.s;
    double l = p1.l - p2.l;

    // Handle the case where we found the bigger angle between two hues:
    if (h > 180) { h = 360 - h; }
    h /= 360;

    return sqrt((h*h) + (s*s) + (l*l));
  }
  
  /**
  * Adds a Point for the bfs traversal to visit at some point in the future.
  * @param work_list the deque storing a list of points to be processed
  * @param point the point to be added
  */
  void bfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    work_list.push_back(point);
  }

  /**
  * Adds a Point for the dfs traversal to visit at some point in the future.
  * @param work_list the deque storing a list of points to be processed
  * @param point the point to be added
  */
  void dfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    work_list.push_back(point);
  }

  /**
  * Removes the current Point in the bfs traversal
  * @param work_list the deque storing a list of points to be processed
  */
  void bfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    work_list.pop_front();
  }

  /**
  * Removes the current Point in the dfs traversal
  * @param work_list the deque storing a list of points to be processed
  */
  void dfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    work_list.pop_back();
  }

  /**
   * Returns the current Point in the bfs traversal
   * @param work_list the deque storing a list of points to be processed
   * @return the current Point 
   */
  Point bfs_peek(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    return work_list.front();
  }

  /**
   * Returns the current Point in the dfs traversal
   * @param work_list the deque storing a list of points to be processed
   * @return the current Point 
   */
  Point dfs_peek(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    return work_list.back();
  }

  /**
  * Initializes a ImageTraversal on a given `png` image,
  * starting at `start`, and with a given `tolerance`.
  * @param png The image this traversal is going to traverse
  * @param start The start point of this traversal
  * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
  * it will not be included in this traversal
  * @param fns the set of functions describing a traversal's operation
  */
  ImageTraversal::ImageTraversal(const PNG & png, const Point & start, double tolerance, TraversalFunctions fns) {  
    /** @todo [Part 1] */
    image = png;
    st = start;
    tol = tolerance;
    function = fns;
  }

  /**
  * Returns an iterator for the traversal starting at the first point.
  */
  ImageTraversal::Iterator ImageTraversal::begin() {
    /** @todo [Part 1] */
    return ImageTraversal::Iterator(st, image, tol, function);
  }

  /**
  * Returns an iterator for the traversal one past the end of the traversal.
  */
  ImageTraversal::Iterator ImageTraversal::end() {
    /** @todo [Part 1] */
    return ImageTraversal::Iterator();
  }

  /**
  * Default iterator constructor.
  */
  ImageTraversal::Iterator::Iterator() {
    /** @todo [Part 1] */
    start_ = Point();
    current_ = Point();
    image_ = PNG();
    tolerance_ = 0;
    function_ = TraversalFunctions();
    path_.resize(0, std::vector<bool>(0));
  }

  /**
   * Custom constructor
  */
  ImageTraversal::Iterator::Iterator(Point start, PNG image, double tolerance, TraversalFunctions func){
    start_ = start;
    current_ = start;
    image_ = image;
    tolerance_ = tolerance;
    function_ = func;
    int height = image.height();
    int width  = image.width();
    path_.resize(width, std::vector<bool>(height));

    // initialize everything to be not visited
    for(int i = 0; i < width; i++){
      for(int j = 0; j < height; j++){
        path_[i][j] = false;
      }
    }
  }


  /**
  * Iterator increment operator.
  *
  * Advances the traversal of the image.
  */
  ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
    /** @todo [Part 1] */

    Point right = Point(current_.x + 1, current_.y);
    Point below = Point(current_.x, current_.y + 1);
    Point left = Point(current_.x - 1, current_.y);
    Point above = Point(current_.x, current_.y - 1);
    path_[current_.x][current_.y] = true;

    while(!work_list_.empty() && path_[function_.peek(work_list_).x][function_.peek(work_list_).y] == true){
      function_.pop(work_list_);
    }

    double temp = 0;

    // Right
    if(right.x < image_.width() && path_[right.x][right.y] == false){
      HSLAPixel pix = image_.getPixel(right.x, right.y);
      HSLAPixel startpix = image_.getPixel(start_.x, start_.y);
      temp = calculateDelta(pix, startpix);
      if(temp < tolerance_){
        function_.add(work_list_, right); 
      }
    }

    // Below
    if(below.y < image_.height() && path_[below.x][below.y] == false){
      HSLAPixel pix = image_.getPixel(below.x, below.y);
      HSLAPixel startpix = image_.getPixel(start_.x, start_.y);
      temp = calculateDelta(pix, startpix);
      if(temp < tolerance_){
        function_.add(work_list_, below);
      }
    }


    // Left
    if(left.x < image_.width() && path_[left.x][left.y] == false){
      HSLAPixel pix = image_.getPixel(left.x, left.y);
      HSLAPixel startpix = image_.getPixel(start_.x, start_.y);
      temp = calculateDelta(pix, startpix);
      if(temp < tolerance_){
        function_.add(work_list_, left);
      }
    }


    // Above
    if(above.y < image_.height() && path_[above.x][above.y] == false){
      HSLAPixel pix = image_.getPixel(above.x, above.y);
      HSLAPixel startpix = image_.getPixel(start_.x, start_.y);
      temp = calculateDelta(pix, startpix);
      if(temp < tolerance_){
        function_.add(work_list_, above);
      }
    }

    
    if(!work_list_.empty()){
      current_ = function_.peek(work_list_);
    }else{
      current_ = Point(-1, -1);
    }

    return *this;
  }

  /**
  * Iterator accessor operator.
  *
  * Accesses the current Point in the ImageTraversal.
  */
  Point ImageTraversal::Iterator::operator*() {
    /** @todo [Part 1] */
    return current_;
  }

  /**
  * Iterator inequality operator.
  *
  * Determines if two iterators are not equal.
  */
  bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
    /** @todo [Part 1] */
    // int count = 0;
    // if(this->work_list_ == other.work_list_){
    //   count = count + 0;
    // }else{
    //   count = count + 1;
    // }
    // if(this->start_ == other.start_){
    //   count = count + 0;
    // }else{
    //   count = count + 1;
    // }
    // if(this->tolerance_ == other.tolerance_){
    //   count = count + 0;
    // }else{
    //   count = count + 1;
    // }

    
    // if(this->current_ == other.current_){
    //   count = count + 0;
    // }else{
    //   count = count + 1;
    // }
    // return count != 0;
    // if(this->current_ == other.current_){
    //   return false;
    // }else{
    //   return true;
    // }

    if(this->current_ == Point(-1, -1)){
      return false;
    }
    return true;
  }

  /**
   * Iterator size function.
   *
   * @return size_t the size of the iterator work queue.
   */
  size_t ImageTraversal::Iterator::size() const {
    return work_list_.size();
  }

  /**
   * Iterator empty function.
   *
   * @return bool whether the iterator work queue is empty.
   */
  bool ImageTraversal::Iterator::empty() const {
    return work_list_.empty();
  }

}