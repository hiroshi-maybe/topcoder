// Delete one element from multiset
void delete(int v, multiset< int > &heap) {
  heap.erase(heap.equal_range(v).first);
}
