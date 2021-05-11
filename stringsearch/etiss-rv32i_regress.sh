bm="ss"
src=(main)
sihft=(x cfcss rasm nzdcfgs nzdc nzdccfcss nzdcrasm)

llc="riscv-llc -O2 -march=riscv32"

gcc="riscv64-unknown-elf-gcc -w -I ../../../etiss_bsp/ -march=rv32i -mabi=ilp32 ../../../etiss_bsp/crt0.riscv.S ../../../etiss_bsp/syscalls.c ../../../etiss_bsp/exceptions.c ../../../etiss_bsp/int.c"
post_gcc="-nostartfiles -T ../../../etiss_bsp/link.ld -lm"






######################################################################

for s in ${src[@]}
do
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
