/// Copyright (c) 2022 Yoshikawa Teru
/// This software is released under the MIT License, see LICENSE.
/// @file Sequence.h
/// @author Yoshikawa Teru
#ifndef RCT_SEQUENCE_H_
#define RCT_SEQUENCE_H_

#include <array>
#include <functional>
#include <utility>

namespace rct {
enum class SequenceStatus {
  proceed,  // 継続
  next,     // 次へ
  reset,    // 最初へ
  end,      // 最後へ
};
// 引数を取らずStatusを返す関数型
using SeqFunc = std::function<SequenceStatus()>;

template<int N>
struct Sequence {
  // Requirement checking for template arguments
  static_assert(0 < N);
  Sequence(const SeqFunc (&args)[N]) noexcept : Sequence{args, std::make_index_sequence<N>{}} {}
  template<std::size_t... I>
  Sequence(const SeqFunc (&args)[N], std::index_sequence<I...>) noexcept : funcs_{args[I]...} {}
  static constexpr int size() noexcept {
    return N;
  }
  void operator()() {
    const SequenceStatus status = funcs_.at(seq_)();
    switch(status) {
      case SequenceStatus::next:
        next();
        break;
      case SequenceStatus::reset:
        reset();
        break;
      case SequenceStatus::end:
        end();
        break;
      case SequenceStatus::proceed:
      default:
        // do nothing
        break;
    }
  }
  void next(const int n = 1) noexcept {
    seq_ += n;
  }
  void reset(const int n = 0) noexcept {
    seq_ = n;
  }
  void end() noexcept {
    seq_ = N - 1;
  }
  int get_index() const noexcept {
    return seq_;
  }
 private:
  std::array<SeqFunc, N> funcs_;
  int seq_ = 0;
};
}  // namespace rct

#endif  // RCT_SEQUENCE_H_
