; ModuleID = 'test.optimized.bc'
source_filename = "test.ll"

define dso_local i32 @foo(i32 noundef %0, i32 noundef %1) {
  %3 = add nsw i32 %1, 2
  %4 = mul nsw i32 %3, 1
  %5 = shl i32 %0, 1
  %6 = sdiv i32 %5, 4
  %7 = lshr i32 %5, 2
  %8 = mul nsw i32 %3, %7
  %9 = mul nsw i32 %8, 8
  %10 = shl i32 %8, 3
  %11 = mul nsw i32 %3, 16
  %12 = shl i32 %3, 4
  %13 = mul nsw i32 %12, 15
  %14 = shl i32 %12, 4
  %15 = sub i32 %14, %12
  %16 = mul nsw i32 16, %12
  %17 = shl i32 %12, 4
  %18 = add nsw i32 %3, 1
  %19 = sub nsw i32 %3, 2
  %20 = add nsw i32 %8, 0
  ret i32 %1
}
