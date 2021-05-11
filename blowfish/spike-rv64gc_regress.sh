bm="bf"
src=(blowfish_test blowfish)
sihft=(x cfcss rasm nzdcfgs nzdc nzdccfcss nzdcrasm)

clang="riscv-clang -emit-llvm --target=riscv64 -march=rv64gc -mabi=lp64d -isystem /home/ga38qoh/eda_tools/riscv/current/riscv64-unknown-elf/include/ -O2 -S"
llc="riscv-llc -O2 -march=riscv64 -mattr=+m,+a,+d,+c"

gcc="riscv64-unknown-elf-gcc -march=rv64gc -mabi=lp64d"
post_gcc=""






######################################################################

for s in ${src[@]}
do
  $clang ../../$s.c

  echo
  echo "...gen for $s"
  $llc ${s}.ll -o ${s}_x.s

  echo
  echo "...gen [cfcss] for $s"
  $llc -CFCSS ${s}.ll -o ${s}_cfcss.s

  echo
  echo "...gen [rasm] for $s"
  $llc -RASM ${s}.ll -o ${s}_rasm.s

  echo
  echo "...gen [nzdc-fgs] for $s"
  $llc -NZDC -FGS ${s}.ll -o ${s}_nzdcfgs.s

  echo
  echo "...gen [nzdc-cgs] for $s"
  $llc -NZDC ${s}.ll -o ${s}_nzdc.s

  echo
  echo "...gen [nzdc-cgs + cfcss] for $s"
  $llc -NZDC -CFCSS ${s}.ll -o ${s}_nzdccfcss.s

  echo
  echo "...gen [nzdc-cgs + rasm] for $s"
  $llc -NZDC -RASM ${s}.ll -o ${s}_nzdcrasm.s
done

for s in ${sihft[@]}
do
  asm_src=()
  for ss in ${src[@]}
  do
    asm_src=(${asm_src[@]} ${ss}_${s}.s)
  done
  
  if [ -f ${bm}_${s}.elf ]
  then
    rm ${bm}_${s}.elf  
  fi
  
  $gcc  ${asm_src[@]} -o ${bm}_${s}.elf $post_gcc
  riscv64-unknown-elf-objdump -d ${bm}_${s}.elf > ${bm}_${s}.dump
done
