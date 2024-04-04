; ModuleID = 'test.optimized.bc'
source_filename = "test.ll"

define dso_local i32 @foo(i32 noundef %0, i32 noundef %1) {
  %3 = add nsw i32 %1, 2
  %4 = mul nsw i32 %3, 1
  %5 = shl i32 %3, 0
  %6 = shl i32 %0, 1
  %7 = sdiv i32 %6, 4
  %8 = lshr i32 %6, 2
  %9 = mul nsw i32 %3, %8
  %10 = mul nsw i32 %9, 8
  %11 = shl i32 %9, 3
  %12 = mul nsw i32 8, 16
  %13 = shl i32 8, 4
  %14 = mul nsw i32 32, 15
  %15 = shl i32 32, 4
  %16 = sub i32 %15, 32
  %17 = mul nsw i32 16, %13
  %18 = shl i32 %13, 4
  %19 = add nsw i32 %3, 1
  %20 = sub nsw i32 %3, 2
  %21 = add nsw i32 %9, 0
  ret i32 %1
}
