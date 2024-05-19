; ModuleID = 'LICM.bc'
source_filename = "LICM.c"
target datalayout = "e-m:e-i8:8:32-i16:16:32-i64:64-i128:128-n32:64-S128"
target triple = "aarch64-unknown-linux-gnu"

@.str = private unnamed_addr constant [25 x i8] c"%d,%d,%d,%d,%d,%d,%d,%d\0A\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local void @foo(i32 noundef %0, i32 noundef %1) #0 !dbg !9 {
  %3 = add nsw i32 %0, 3, !dbg !12
  %4 = add nsw i32 %0, 7, !dbg !13
  %5 = add nsw i32 %0, 4, !dbg !14
  br label %6, !dbg !15

6:                                                ; preds = %17, %2
  %.05 = phi i32 [ 0, %2 ], [ %21, %17 ], !dbg !16
  %.04 = phi i32 [ 0, %2 ], [ %19, %17 ], !dbg !16
  %.03 = phi i32 [ 0, %2 ], [ %18, %17 ], !dbg !16
  %.01 = phi i32 [ 9, %2 ], [ %.1, %17 ], !dbg !16
  %.0 = phi i32 [ %1, %2 ], [ %7, %17 ]
  %7 = add nsw i32 %.0, 1, !dbg !17
  %8 = icmp slt i32 %7, 5, !dbg !18
  br i1 %8, label %9, label %12, !dbg !19

9:                                                ; preds = %6
  %10 = add nsw i32 %.01, 2, !dbg !20
  %11 = add nsw i32 %0, 3, !dbg !21
  br label %17, !dbg !22

12:                                               ; preds = %6
  %13 = sub nsw i32 %.01, 1, !dbg !23
  %14 = icmp sge i32 %7, 10, !dbg !24
  br i1 %14, label %15, label %16, !dbg !25

15:                                               ; preds = %12
  %.lcssa4 = phi i32 [ %13, %12 ], !dbg !23
  %.lcssa3 = phi i32 [ %5, %12 ], !dbg !14
  %.05.lcssa = phi i32 [ %.05, %12 ], !dbg !16
  %.04.lcssa = phi i32 [ %.04, %12 ], !dbg !16
  %.03.lcssa = phi i32 [ %.03, %12 ], !dbg !16
  %.lcssa2 = phi i32 [ %7, %12 ], !dbg !17
  %.lcssa1 = phi i32 [ %3, %12 ], !dbg !12
  %.lcssa = phi i32 [ %4, %12 ], !dbg !13
  br label %22, !dbg !26

16:                                               ; preds = %12
  br label %17

17:                                               ; preds = %16, %9
  %.02 = phi i32 [ %11, %9 ], [ %5, %16 ], !dbg !16
  %.1 = phi i32 [ %10, %9 ], [ %13, %16 ], !dbg !16
  %18 = add nsw i32 %3, 7, !dbg !27
  %19 = add nsw i32 %.02, 2, !dbg !28
  %20 = add nsw i32 %0, 7, !dbg !29
  %21 = add nsw i32 %4, 5, !dbg !30
  br label %6, !dbg !31

22:                                               ; preds = %15
  %23 = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %.lcssa4, i32 noundef %.lcssa3, i32 noundef %.03.lcssa, i32 noundef %.04.lcssa, i32 noundef %.lcssa, i32 noundef %.05.lcssa, i32 noundef %.lcssa1, i32 noundef %.lcssa2), !dbg !32
  ret void, !dbg !33
}

declare i32 @printf(ptr noundef, ...) #1

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !34 {
  call void @foo(i32 noundef 0, i32 noundef 4), !dbg !35
  call void @foo(i32 noundef 0, i32 noundef 12), !dbg !36
  ret i32 0, !dbg !37
}

attributes #0 = { noinline nounwind uwtable "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" "target-features"="+fp-armv8,+neon,+outline-atomics,+v8a,-fmv" }
attributes #1 = { "frame-pointer"="non-leaf" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="generic" "target-features"="+fp-armv8,+neon,+outline-atomics,+v8a,-fmv" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!2, !3, !4, !5, !6, !7}
!llvm.ident = !{!8}

!0 = distinct !DICompileUnit(language: DW_LANG_C11, file: !1, producer: "clang version 17.0.6 (https://github.com/llvm/llvm-project.git 6009708b4367171ccdbf4b5905cb6a803753fe18)", isOptimized: false, runtimeVersion: 0, emissionKind: NoDebug, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "LICM.c", directory: "/home/matteo/LLVM/TEST")
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = !{i32 1, !"wchar_size", i32 4}
!4 = !{i32 8, !"PIC Level", i32 2}
!5 = !{i32 7, !"PIE Level", i32 2}
!6 = !{i32 7, !"uwtable", i32 2}
!7 = !{i32 7, !"frame-pointer", i32 1}
!8 = !{!"clang version 17.0.6 (https://github.com/llvm/llvm-project.git 6009708b4367171ccdbf4b5905cb6a803753fe18)"}
!9 = distinct !DISubprogram(name: "foo", scope: !1, file: !1, line: 3, type: !10, scopeLine: 3, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0)
!10 = !DISubroutineType(types: !11)
!11 = !{}
!12 = !DILocation(line: 8, column: 9, scope: !9)
!13 = !DILocation(line: 9, column: 9, scope: !9)
!14 = !DILocation(line: 15, column: 11, scope: !9)
!15 = !DILocation(line: 4, column: 3, scope: !9)
!16 = !DILocation(line: 0, scope: !9)
!17 = !DILocation(line: 7, column: 9, scope: !9)
!18 = !DILocation(line: 10, column: 9, scope: !9)
!19 = !DILocation(line: 10, column: 7, scope: !9)
!20 = !DILocation(line: 11, column: 11, scope: !9)
!21 = !DILocation(line: 12, column: 11, scope: !9)
!22 = !DILocation(line: 13, column: 3, scope: !9)
!23 = !DILocation(line: 14, column: 11, scope: !9)
!24 = !DILocation(line: 16, column: 11, scope: !9)
!25 = !DILocation(line: 16, column: 9, scope: !9)
!26 = !DILocation(line: 17, column: 7, scope: !9)
!27 = !DILocation(line: 20, column: 9, scope: !9)
!28 = !DILocation(line: 21, column: 9, scope: !9)
!29 = !DILocation(line: 22, column: 9, scope: !9)
!30 = !DILocation(line: 23, column: 9, scope: !9)
!31 = !DILocation(line: 24, column: 3, scope: !9)
!32 = !DILocation(line: 26, column: 3, scope: !9)
!33 = !DILocation(line: 27, column: 1, scope: !9)
!34 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 29, type: !10, scopeLine: 29, spFlags: DISPFlagDefinition, unit: !0)
!35 = !DILocation(line: 30, column: 3, scope: !34)
!36 = !DILocation(line: 31, column: 3, scope: !34)
!37 = !DILocation(line: 32, column: 3, scope: !34)
