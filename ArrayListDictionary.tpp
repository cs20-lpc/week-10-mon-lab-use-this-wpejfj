template <typename Key, typename Val>
unsigned ArrayListDictionary<Key, Val>::numComps = 0;

template <typename Key, typename Val>
ArrayListDictionary<Key, Val>::ArrayListDictionary(int i)
: list(new ArrayList<Record>(i)) { }

template <typename Key, typename Val>
ArrayListDictionary<Key, Val>::ArrayListDictionary(const ArrayListDictionary<Key, Val>& copyObj) {
    copy(copyObj);
}

template <typename Key, typename Val>
ArrayListDictionary<Key, Val>& ArrayListDictionary<Key, Val>::operator=(const ArrayListDictionary<Key, Val>& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}

template <typename Key, typename Val>
ArrayListDictionary<Key, Val>::~ArrayListDictionary() {
    delete list;
}

template <typename Key, typename Val>
Val ArrayListDictionary<Key, Val>::binSearchIter(const Key& target, int left, int right) const {
    // TODO
  while (left <= right) {
    int mid = left + (right - left) / 2;
    Record rec = list->getElement(mid);

    ++numComps;
    if (rec.k == target) {
      return rec.v;
    }
    ++numComps;
    if (target < rec.k) {
      right = mid - 1;
    }
    else {
      left = mid + 1;
    }
  }

  throw -1;

}

template <typename Key, typename Val>
Val ArrayListDictionary<Key, Val>::binSearchRec(const Key& target, int left, int right) const {
    // TODO
  if (left > right) {
    throw -1;
  }

  int mid = left + (right - left) / 2;
  Record rec = list->getElement(mid);

  ++numComps;
  if (rec.k == target) {
    return rec.v;
  }
  
  ++numComps;
  if (target < rec.k) {
    return binSearchRec(target, left, mid - 1);
  }
  else {
    return binSearchRec(target, mid + 1, right);
  }
		     

}

template <typename Key, typename Val>
void ArrayListDictionary<Key, Val>::clear() {
    list->clear();
}

template <typename Key, typename Val>
void ArrayListDictionary<Key, Val>::copy(const ArrayListDictionary<Key, Val>& copyObj) {
    list = new ArrayList<Record>(*copyObj.list);
}

template <typename Key, typename Val>
Val ArrayListDictionary<Key, Val>::find(const Key& k) const {
    numComps = 0;

    try {
      // return seqSearchIter(k);
        // return seqSearchRec(k);
      return binSearchIter(k, 0, list->getLength() - 1);
        // return binSearchRec(k, 0, list->getLength() - 1);
    }
    catch (...) {
        throw string("find: error, unsuccessful search, target key not found");
    }
}

template <typename Key, typename Val>
unsigned ArrayListDictionary<Key, Val>::getNumComps() {
    return numComps;
}

template <typename Key, typename Val>
void ArrayListDictionary<Key, Val>::insert(const Key& k, const Val& v) {
    list->append(Record(k, v));
}

template <typename Key, typename Val>
void ArrayListDictionary<Key, Val>::remove(const Key& k) {
    bool flag = false;

    for (int i = 0; i < list->getLength(); i++) {
        if (list->getElement(i).k == k) {
            list->remove(i);
            flag = true;
            break;
        }
    }

    if (!flag) {
        throw string("remove: error, unable to find record with matching key to remove");
    }
}

template <typename Key, typename Val>
Val ArrayListDictionary<Key, Val>::seqSearchIter(const Key& target) const {
    // TODO
  for (int i = 0; i < list->getLength(); ++i) {
    ++numComps;
    if (list->getElement(i).k == target) {
      return list->getElement(i).v;
    }
  }
  throw -1;

}

template <typename Key, typename Val>
Val ArrayListDictionary<Key, Val>::seqSearchRec(const Key& target, int i) const {
    // TODO
  if (i >= list->getLength()) {
    throw -1;
  }

  ++numComps;
  if (list->getElement(i).k == target) {
    return list->getElement(i).v;
  }

  return seqSearchRec(target, i + 1);
  
}

template <typename Key, typename Val>
int ArrayListDictionary<Key, Val>::size() const {
    return list->getLength();
}
