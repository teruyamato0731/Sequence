#include <Sequence.h>

#include <cstdio>

using namespace rct;

int main() {
  Sequence seq = {[] {
                    printf("hoge\n");
                    return SequenceStatus::next;
                  },
                  [] {
                    printf("fuga\n");
                    return SequenceStatus::next;
                  },
                  [] {
                    printf("piyo\n");
                    return SequenceStatus::next;
                  }};
  while(seq.get_index() < seq.size()) {
    seq();
  }
}
