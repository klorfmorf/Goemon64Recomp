.include "macro.inc"

.set noat
.set noreorder

.section .rodata, "a"

dlabel jtbl_8020BA60_5C7970
    /* 5C7970 8020BA60 801EBFA8 */ .word .L801EBFA8_5A7EB8
    /* 5C7974 8020BA64 801EC098 */ .word .L801EC098_5A7FA8
    /* 5C7978 8020BA68 801EC234 */ .word .L801EC234_5A8144
    /* 5C797C 8020BA6C 801EC284 */ .word .L801EC284_5A8194
    /* 5C7980 8020BA70 801EC350 */ .word .L801EC350_5A8260
enddlabel jtbl_8020BA60_5C7970

.section .recomp_patch, "ax"

glabel func_801EBF48_5A7E58
    /* 5A7E58 801EBF48 27BDFF20 */  addiu      $sp, $sp, -0xE0
    /* 5A7E5C 801EBF4C AFBF003C */  sw         $ra, 0x3C($sp)
    /* 5A7E60 801EBF50 AFB20038 */  sw         $s2, 0x38($sp)
    /* 5A7E64 801EBF54 AFB10034 */  sw         $s1, 0x34($sp)
    /* 5A7E68 801EBF58 AFB00030 */  sw         $s0, 0x30($sp)
    /* 5A7E6C 801EBF5C AFA500E4 */  sw         $a1, 0xE4($sp)
    /* 5A7E70 801EBF60 AFA600E8 */  sw         $a2, 0xE8($sp)
    /* 5A7E74 801EBF64 AFA700EC */  sw         $a3, 0xEC($sp)
    /* 5A7E78 801EBF68 8C900018 */  lw         $s0, 0x18($a0)
    /* 5A7E7C 801EBF6C 8C83005C */  lw         $v1, 0x5C($a0)
    /* 5A7E80 801EBF70 00808825 */  or         $s1, $a0, $zero
    /* 5A7E84 801EBF74 8E0E0000 */  lw         $t6, 0x0($s0)
    /* 5A7E88 801EBF78 8C720018 */  lw         $s2, 0x18($v1)
    /* 5A7E8C 801EBF7C 8DCF0000 */  lw         $t7, 0x0($t6)
    /* 5A7E90 801EBF80 AFAF00CC */  sw         $t7, 0xCC($sp)
    /* 5A7E94 801EBF84 90980060 */  lbu        $t8, 0x60($a0)
    /* 5A7E98 801EBF88 2F010005 */  sltiu      $at, $t8, 0x5
    /* 5A7E9C 801EBF8C 1020011B */  beqz       $at, .L801EC3FC_5A830C
    /* 5A7EA0 801EBF90 0018C080 */   sll       $t8, $t8, 2
    /* 5A7EA4 801EBF94 3C018021 */  lui        $at, %hi(jtbl_8020BA60_5C7970)
    /* 5A7EA8 801EBF98 00380821 */  addu       $at, $at, $t8
    /* 5A7EAC 801EBF9C 8C38BA60 */  lw         $t8, %lo(jtbl_8020BA60_5C7970)($at)
    /* 5A7EB0 801EBFA0 03000008 */  jr         $t8
    /* 5A7EB4 801EBFA4 00000000 */   nop
  .L801EBFA8_5A7EB8:
    /* 5A7EB8 801EBFA8 2404FFFF */  addiu      $a0, $zero, -0x1
    /* 5A7EBC 801EBFAC 0C07733C */  jal        func_801DCCF0_598C00
    /* 5A7EC0 801EBFB0 AFA300D4 */   sw        $v1, 0xD4($sp)
    /* 5A7EC4 801EBFB4 02402025 */  or         $a0, $s2, $zero
    /* 5A7EC8 801EBFB8 0C07B8A3 */  jal        func_801EE28C_5AA19C
    /* 5A7ECC 801EBFBC 02002825 */   or        $a1, $s0, $zero
    /* 5A7ED0 801EBFC0 C7A400EC */  lwc1       $f4, 0xEC($sp)
    /* 5A7ED4 801EBFC4 02402025 */  or         $a0, $s2, $zero
    /* 5A7ED8 801EBFC8 02002825 */  or         $a1, $s0, $zero
    /* 5A7EDC 801EBFCC 8FA600E4 */  lw         $a2, 0xE4($sp)
    /* 5A7EE0 801EBFD0 8FA700E8 */  lw         $a3, 0xE8($sp)
    /* 5A7EE4 801EBFD4 0C07B94C */  jal        func_801EE530_5AA440
    /* 5A7EE8 801EBFD8 E7A40010 */   swc1      $f4, 0x10($sp)
    /* 5A7EEC 801EBFDC 2419001E */  addiu      $t9, $zero, 0x1E
    /* 5A7EF0 801EBFE0 AFB90010 */  sw         $t9, 0x10($sp)
    /* 5A7EF4 801EBFE4 02202025 */  or         $a0, $s1, $zero
    /* 5A7EF8 801EBFE8 24050002 */  addiu      $a1, $zero, 0x2
    /* 5A7EFC 801EBFEC 2406FFFF */  addiu      $a2, $zero, -0x1
    /* 5A7F00 801EBFF0 2407001C */  addiu      $a3, $zero, 0x1C
    /* 5A7F04 801EBFF4 AFA00014 */  sw         $zero, 0x14($sp)
    /* 5A7F08 801EBFF8 0C07B88A */  jal        func_801EE228_5AA138
    /* 5A7F0C 801EBFFC AFA00018 */   sw        $zero, 0x18($sp)
    /* 5A7F10 801EC000 8FA300D4 */  lw         $v1, 0xD4($sp)
    /* 5A7F14 801EC004 3C0140A0 */  lui        $at, (0x40A00000 >> 16)
    /* 5A7F18 801EC008 44815000 */  mtc1       $at, $f10
    /* 5A7F1C 801EC00C C4660068 */  lwc1       $f6, 0x68($v1)
    /* 5A7F20 801EC010 3C014040 */  lui        $at, (0x40400000 >> 16)
    /* 5A7F24 801EC014 44812000 */  mtc1       $at, $f4
    /* 5A7F28 801EC018 E7A600BC */  swc1       $f6, 0xBC($sp)
    /* 5A7F2C 801EC01C C468006C */  lwc1       $f8, 0x6C($v1)
    /* 5A7F30 801EC020 27A900B8 */  addiu      $t1, $sp, 0xB8
    /* 5A7F34 801EC024 27AA00B4 */  addiu      $t2, $sp, 0xB4
    /* 5A7F38 801EC028 460A4400 */  add.s      $f16, $f8, $f10
    /* 5A7F3C 801EC02C 27A700BC */  addiu      $a3, $sp, 0xBC
    /* 5A7F40 801EC030 E7B000B8 */  swc1       $f16, 0xB8($sp)
    /* 5A7F44 801EC034 C4720070 */  lwc1       $f18, 0x70($v1)
    /* 5A7F48 801EC038 46049180 */  add.s      $f6, $f18, $f4
    /* 5A7F4C 801EC03C E7A600B4 */  swc1       $f6, 0xB4($sp)
    /* 5A7F50 801EC040 96460018 */  lhu        $a2, 0x18($s2)
    /* 5A7F54 801EC044 96450016 */  lhu        $a1, 0x16($s2)
    /* 5A7F58 801EC048 96440014 */  lhu        $a0, 0x14($s2)
    /* 5A7F5C 801EC04C AFAA0014 */  sw         $t2, 0x14($sp)
    /* 5A7F60 801EC050 0C00CE26 */  jal        func_80033898_34498
    /* 5A7F64 801EC054 AFA90010 */   sw        $t1, 0x10($sp)
    /* 5A7F68 801EC058 C7A800BC */  lwc1       $f8, 0xBC($sp)
    /* 5A7F6C 801EC05C 922C0060 */  lbu        $t4, 0x60($s1)
    /* 5A7F70 801EC060 240B005A */  addiu      $t3, $zero, 0x5A
    /* 5A7F74 801EC064 E628006C */  swc1       $f8, 0x6C($s1)
    /* 5A7F78 801EC068 C7AA00B8 */  lwc1       $f10, 0xB8($sp)
    /* 5A7F7C 801EC06C 258D0001 */  addiu      $t5, $t4, 0x1
    /* 5A7F80 801EC070 02002025 */  or         $a0, $s0, $zero
    /* 5A7F84 801EC074 E62A0070 */  swc1       $f10, 0x70($s1)
    /* 5A7F88 801EC078 C7B000B4 */  lwc1       $f16, 0xB4($sp)
    /* 5A7F8C 801EC07C A62B0062 */  sh         $t3, 0x62($s1)
    /* 5A7F90 801EC080 A22D0060 */  sb         $t5, 0x60($s1)
    /* 5A7F94 801EC084 E6300074 */  swc1       $f16, 0x74($s1)
    /* 5A7F98 801EC088 0C07B858 */  jal        func_801EE160_5AA070
    /* 5A7F9C 801EC08C 8FA500CC */   lw        $a1, 0xCC($sp)
    /* 5A7FA0 801EC090 100000DB */  b          .L801EC400_5A8310
    /* 5A7FA4 801EC094 8FBF003C */   lw        $ra, 0x3C($sp)
  .L801EC098_5A7FA8:
    /* 5A7FA8 801EC098 962E0062 */  lhu        $t6, 0x62($s1)
    /* 5A7FAC 801EC09C 24190001 */  addiu      $t9, $zero, 0x1
    /* 5A7FB0 801EC0A0 3C018021 */  lui        $at, %hi(D_8020BA74_5C7984)
    /* 5A7FB4 801EC0A4 25CFFFFF */  addiu      $t7, $t6, -0x1
    /* 5A7FB8 801EC0A8 31F8FFFF */  andi       $t8, $t7, 0xFFFF
    /* 5A7FBC 801EC0AC 1F000003 */  bgtz       $t8, .L801EC0BC_5A7FCC
    /* 5A7FC0 801EC0B0 A62F0062 */   sh        $t7, 0x62($s1)
    /* 5A7FC4 801EC0B4 100000D1 */  b          .L801EC3FC_5A830C
    /* 5A7FC8 801EC0B8 A2390065 */   sb        $t9, 0x65($s1)
  .L801EC0BC_5A7FCC:
    /* 5A7FCC 801EC0BC C6320070 */  lwc1       $f18, 0x70($s1)
    /* 5A7FD0 801EC0C0 C424BA74 */  lwc1       $f4, %lo(D_8020BA74_5C7984)($at)
    /* 5A7FD4 801EC0C4 C62A006C */  lwc1       $f10, 0x6C($s1)
    /* 5A7FD8 801EC0C8 46049180 */  add.s      $f6, $f18, $f4
    /* 5A7FDC 801EC0CC E6260070 */  swc1       $f6, 0x70($s1)
    /* 5A7FE0 801EC0D0 C6080008 */  lwc1       $f8, 0x8($s0)
    /* 5A7FE4 801EC0D4 C612000C */  lwc1       $f18, 0xC($s0)
    /* 5A7FE8 801EC0D8 460A4400 */  add.s      $f16, $f8, $f10
    /* 5A7FEC 801EC0DC C6080010 */  lwc1       $f8, 0x10($s0)
    /* 5A7FF0 801EC0E0 E6100008 */  swc1       $f16, 0x8($s0)
    /* 5A7FF4 801EC0E4 C6240070 */  lwc1       $f4, 0x70($s1)
    /* 5A7FF8 801EC0E8 46049180 */  add.s      $f6, $f18, $f4
    /* 5A7FFC 801EC0EC E606000C */  swc1       $f6, 0xC($s0)
    /* 5A8000 801EC0F0 C62A0074 */  lwc1       $f10, 0x74($s1)
    /* 5A8004 801EC0F4 460A4400 */  add.s      $f16, $f8, $f10
    /* 5A8008 801EC0F8 E6100010 */  swc1       $f16, 0x10($s0)
    /* 5A800C 801EC0FC 8E290034 */  lw         $t1, 0x34($s1)
    /* 5A8010 801EC100 51200006 */  beql       $t1, $zero, .L801EC11C_5A802C
    /* 5A8014 801EC104 C632006C */   lwc1      $f18, 0x6C($s1)
    /* 5A8018 801EC108 922A0060 */  lbu        $t2, 0x60($s1)
    /* 5A801C 801EC10C 254B0001 */  addiu      $t3, $t2, 0x1
    /* 5A8020 801EC110 100000BA */  b          .L801EC3FC_5A830C
    /* 5A8024 801EC114 A22B0060 */   sb        $t3, 0x60($s1)
    /* 5A8028 801EC118 C632006C */  lwc1       $f18, 0x6C($s1)
  .L801EC11C_5A802C:
    /* 5A802C 801EC11C 27A40060 */  addiu      $a0, $sp, 0x60
    /* 5A8030 801EC120 E7B20060 */  swc1       $f18, 0x60($sp)
    /* 5A8034 801EC124 C6240070 */  lwc1       $f4, 0x70($s1)
    /* 5A8038 801EC128 E7A40064 */  swc1       $f4, 0x64($sp)
    /* 5A803C 801EC12C C6260074 */  lwc1       $f6, 0x74($s1)
    /* 5A8040 801EC130 0C0074E5 */  jal        func_8001D394_1DF94
    /* 5A8044 801EC134 E7A60068 */   swc1      $f6, 0x68($sp)
    /* 5A8048 801EC138 3C0141F0 */  lui        $at, (0x41F00000 >> 16)
    /* 5A804C 801EC13C 44810000 */  mtc1       $at, $f0
    /* 5A8050 801EC140 C60A001C */  lwc1       $f10, 0x1C($s0)
    /* 5A8054 801EC144 C7A80060 */  lwc1       $f8, 0x60($sp)
    /* 5A8058 801EC148 C7A40064 */  lwc1       $f4, 0x64($sp)
    /* 5A805C 801EC14C 460A0402 */  mul.s      $f16, $f0, $f10
    /* 5A8060 801EC150 27A4006C */  addiu      $a0, $sp, 0x6C
    /* 5A8064 801EC154 46104482 */  mul.s      $f18, $f8, $f16
    /* 5A8068 801EC158 C7B00068 */  lwc1       $f16, 0x68($sp)
    /* 5A806C 801EC15C E7B20060 */  swc1       $f18, 0x60($sp)
    /* 5A8070 801EC160 C6060020 */  lwc1       $f6, 0x20($s0)
    /* 5A8074 801EC164 46060282 */  mul.s      $f10, $f0, $f6
    /* 5A8078 801EC168 00000000 */  nop
    /* 5A807C 801EC16C 460A2202 */  mul.s      $f8, $f4, $f10
    /* 5A8080 801EC170 E7A80064 */  swc1       $f8, 0x64($sp)
    /* 5A8084 801EC174 C6060024 */  lwc1       $f6, 0x24($s0)
    /* 5A8088 801EC178 46060102 */  mul.s      $f4, $f0, $f6
    /* 5A808C 801EC17C 00000000 */  nop
    /* 5A8090 801EC180 46048282 */  mul.s      $f10, $f16, $f4
    /* 5A8094 801EC184 E7AA0068 */  swc1       $f10, 0x68($sp)
    /* 5A8098 801EC188 C6060008 */  lwc1       $f6, 0x8($s0)
    /* 5A809C 801EC18C 46069400 */  add.s      $f16, $f18, $f6
    /* 5A80A0 801EC190 E7B00060 */  swc1       $f16, 0x60($sp)
    /* 5A80A4 801EC194 C604000C */  lwc1       $f4, 0xC($s0)
    /* 5A80A8 801EC198 44058000 */  mfc1       $a1, $f16
    /* 5A80AC 801EC19C 46044480 */  add.s      $f18, $f8, $f4
    /* 5A80B0 801EC1A0 E7B20064 */  swc1       $f18, 0x64($sp)
    /* 5A80B4 801EC1A4 C6060010 */  lwc1       $f6, 0x10($s0)
    /* 5A80B8 801EC1A8 44069000 */  mfc1       $a2, $f18
    /* 5A80BC 801EC1AC 46065200 */  add.s      $f8, $f10, $f6
    /* 5A80C0 801EC1B0 E7A80068 */  swc1       $f8, 0x68($sp)
    /* 5A80C4 801EC1B4 C624006C */  lwc1       $f4, 0x6C($s1)
    /* 5A80C8 801EC1B8 44074000 */  mfc1       $a3, $f8
    /* 5A80CC 801EC1BC E7A40010 */  swc1       $f4, 0x10($sp)
    /* 5A80D0 801EC1C0 C62A0070 */  lwc1       $f10, 0x70($s1)
    /* 5A80D4 801EC1C4 E7AA0014 */  swc1       $f10, 0x14($sp)
    /* 5A80D8 801EC1C8 C6260074 */  lwc1       $f6, 0x74($s1)
    /* 5A80DC 801EC1CC 0C00A916 */  jal        func_8002A458_2B058
    /* 5A80E0 801EC1D0 E7A60018 */   swc1      $f6, 0x18($sp)
    /* 5A80E4 801EC1D4 87AC00A4 */  lh         $t4, 0xA4($sp)
    /* 5A80E8 801EC1D8 24017FFF */  addiu      $at, $zero, 0x7FFF
    /* 5A80EC 801EC1DC C7B20084 */  lwc1       $f18, 0x84($sp)
    /* 5A80F0 801EC1E0 15810010 */  bne        $t4, $at, .L801EC224_5A8134
    /* 5A80F4 801EC1E4 02002025 */   or        $a0, $s0, $zero
    /* 5A80F8 801EC1E8 C6100008 */  lwc1       $f16, 0x8($s0)
    /* 5A80FC 801EC1EC C604000C */  lwc1       $f4, 0xC($s0)
    /* 5A8100 801EC1F0 46128200 */  add.s      $f8, $f16, $f18
    /* 5A8104 801EC1F4 C6100010 */  lwc1       $f16, 0x10($s0)
    /* 5A8108 801EC1F8 E6080008 */  swc1       $f8, 0x8($s0)
    /* 5A810C 801EC1FC C7AA0088 */  lwc1       $f10, 0x88($sp)
    /* 5A8110 801EC200 460A2180 */  add.s      $f6, $f4, $f10
    /* 5A8114 801EC204 E606000C */  swc1       $f6, 0xC($s0)
    /* 5A8118 801EC208 C7B2008C */  lwc1       $f18, 0x8C($sp)
    /* 5A811C 801EC20C 46128200 */  add.s      $f8, $f16, $f18
    /* 5A8120 801EC210 E6080010 */  swc1       $f8, 0x10($s0)
    /* 5A8124 801EC214 922D0060 */  lbu        $t5, 0x60($s1)
    /* 5A8128 801EC218 25AE0001 */  addiu      $t6, $t5, 0x1
    /* 5A812C 801EC21C 10000077 */  b          .L801EC3FC_5A830C
    /* 5A8130 801EC220 A22E0060 */   sb        $t6, 0x60($s1)
  .L801EC224_5A8134:
    /* 5A8134 801EC224 0C07B858 */  jal        func_801EE160_5AA070
    /* 5A8138 801EC228 8FA500CC */   lw        $a1, 0xCC($sp)
    /* 5A813C 801EC22C 10000074 */  b          .L801EC400_5A8310
    /* 5A8140 801EC230 8FBF003C */   lw        $ra, 0x3C($sp)
  .L801EC234_5A8144:
    /* 5A8144 801EC234 3C0F8020 */  lui        $t7, %hi(D_801FC628_5B8538)
    /* 5A8148 801EC238 8DEFC628 */  lw         $t7, %lo(D_801FC628_5B8538)($t7)
    /* 5A814C 801EC23C 24040104 */  addiu      $a0, $zero, 0x104
    /* 5A8150 801EC240 02003025 */  or         $a2, $s0, $zero
    /* 5A8154 801EC244 3C0743FA */  lui        $a3, (0x43FA0000 >> 16)
    /* ------ -------- 3C058021 */  lui        $a1, %hi(D_8020CBF0_5C8B00) /* @recomp Add instruction to load direct pointer to camera object */
    /* 5A8158 801EC248 0C003D08 */  jal        func_8000F420_10020
#   /* 5A815C 801EC24C 8DE5002C */   lw        $a1, 0x2C($t7)
    /* 5A815C 801EC24C 24A5CBF0 */  addiu      $a1, $a1, %lo(D_8020CBF0_5C8B00) /* @recomp Replace instruction loading offset 0x2C from $t7 with load of direct pointer to camera object */
    /* 5A8160 801EC250 0C07B105 */  jal        func_801EC414_5A8324
    /* 5A8164 801EC254 02202025 */   or        $a0, $s1, $zero
    /* 5A8168 801EC258 8FB900CC */  lw         $t9, 0xCC($sp)
    /* 5A816C 801EC25C 24180001 */  addiu      $t8, $zero, 0x1
    /* 5A8170 801EC260 44802000 */  mtc1       $zero, $f4
    /* 5A8174 801EC264 A3380064 */  sb         $t8, 0x64($t9)
    /* 5A8178 801EC268 922A0060 */  lbu        $t2, 0x60($s1)
    /* 5A817C 801EC26C 24090064 */  addiu      $t1, $zero, 0x64
    /* 5A8180 801EC270 A629004E */  sh         $t1, 0x4E($s1)
    /* 5A8184 801EC274 254B0001 */  addiu      $t3, $t2, 0x1
    /* 5A8188 801EC278 A22B0060 */  sb         $t3, 0x60($s1)
    /* 5A818C 801EC27C 1000005F */  b          .L801EC3FC_5A830C
    /* 5A8190 801EC280 E624009C */   swc1      $f4, 0x9C($s1)
  .L801EC284_5A8194:
    /* 5A8194 801EC284 3C018021 */  lui        $at, %hi(D_8020BA78_5C7988)
    /* 5A8198 801EC288 C42EBA78 */  lwc1       $f14, %lo(D_8020BA78_5C7988)($at)
    /* 5A819C 801EC28C 3C018021 */  lui        $at, %hi(D_8020BA7C_5C798C)
    /* 5A81A0 801EC290 C426BA7C */  lwc1       $f6, %lo(D_8020BA7C_5C798C)($at)
    /* 5A81A4 801EC294 C62A009C */  lwc1       $f10, 0x9C($s1)
    /* 5A81A8 801EC298 3C018021 */  lui        $at, %hi(D_8020BA80_5C7990)
    /* 5A81AC 801EC29C 263200A0 */  addiu      $s2, $s1, 0xA0
    /* 5A81B0 801EC2A0 46065400 */  add.s      $f16, $f10, $f6
    /* 5A81B4 801EC2A4 E630009C */  swc1       $f16, 0x9C($s1)
    /* 5A81B8 801EC2A8 C622009C */  lwc1       $f2, 0x9C($s1)
    /* 5A81BC 801EC2AC C428BA80 */  lwc1       $f8, %lo(D_8020BA80_5C7990)($at)
    /* 5A81C0 801EC2B0 C612001C */  lwc1       $f18, 0x1C($s0)
    /* 5A81C4 801EC2B4 46021302 */  mul.s      $f12, $f2, $f2
    /* 5A81C8 801EC2B8 00000000 */  nop
    /* 5A81CC 801EC2BC 460C4102 */  mul.s      $f4, $f8, $f12
    /* 5A81D0 801EC2C0 46049280 */  add.s      $f10, $f18, $f4
    /* 5A81D4 801EC2C4 E60A001C */  swc1       $f10, 0x1C($s0)
    /* 5A81D8 801EC2C8 C600001C */  lwc1       $f0, 0x1C($s0)
    /* 5A81DC 801EC2CC 4600703C */  c.lt.s     $f14, $f0
    /* 5A81E0 801EC2D0 00000000 */  nop
    /* 5A81E4 801EC2D4 45000006 */  bc1f       .L801EC2F0_5A8200
    /* 5A81E8 801EC2D8 00000000 */   nop
    /* 5A81EC 801EC2DC E60E001C */  swc1       $f14, 0x1C($s0)
    /* 5A81F0 801EC2E0 922C0060 */  lbu        $t4, 0x60($s1)
    /* 5A81F4 801EC2E4 258D0001 */  addiu      $t5, $t4, 0x1
    /* 5A81F8 801EC2E8 A22D0060 */  sb         $t5, 0x60($s1)
    /* 5A81FC 801EC2EC C600001C */  lwc1       $f0, 0x1C($s0)
  .L801EC2F0_5A8200:
    /* 5A8200 801EC2F0 8E020000 */  lw         $v0, 0x0($s0)
    /* 5A8204 801EC2F4 E6000024 */  swc1       $f0, 0x24($s0)
    /* 5A8208 801EC2F8 E6000020 */  swc1       $f0, 0x20($s0)
    /* 5A820C 801EC2FC E440001C */  swc1       $f0, 0x1C($v0)
    /* 5A8210 801EC300 E4400020 */  swc1       $f0, 0x20($v0)
    /* 5A8214 801EC304 E4400024 */  swc1       $f0, 0x24($v0)
    /* 5A8218 801EC308 AFA00014 */  sw         $zero, 0x14($sp)
    /* 5A821C 801EC30C AFA00010 */  sw         $zero, 0x10($sp)
    /* 5A8220 801EC310 924E0001 */  lbu        $t6, 0x1($s2)
    /* 5A8224 801EC314 3C068020 */  lui        $a2, %hi(D_802049C0_5C08D0)
    /* 5A8228 801EC318 24C649C0 */  addiu      $a2, $a2, %lo(D_802049C0_5C08D0)
    /* 5A822C 801EC31C AFAE0018 */  sw         $t6, 0x18($sp)
    /* 5A8230 801EC320 924F0002 */  lbu        $t7, 0x2($s2)
    /* 5A8234 801EC324 00002025 */  or         $a0, $zero, $zero
    /* 5A8238 801EC328 262500A8 */  addiu      $a1, $s1, 0xA8
    /* 5A823C 801EC32C AFAF001C */  sw         $t7, 0x1C($sp)
    /* 5A8240 801EC330 92580003 */  lbu        $t8, 0x3($s2)
    /* 5A8244 801EC334 00003825 */  or         $a3, $zero, $zero
    /* 5A8248 801EC338 AFB80020 */  sw         $t8, 0x20($sp)
    /* 5A824C 801EC33C 92590000 */  lbu        $t9, 0x0($s2)
    /* 5A8250 801EC340 0C077155 */  jal        func_801DC554_598464
    /* 5A8254 801EC344 AFB90024 */   sw        $t9, 0x24($sp)
    /* 5A8258 801EC348 1000002D */  b          .L801EC400_5A8310
    /* 5A825C 801EC34C 8FBF003C */   lw        $ra, 0x3C($sp)
  .L801EC350_5A8260:
    /* 5A8260 801EC350 263200A0 */  addiu      $s2, $s1, 0xA0
    /* 5A8264 801EC354 02402025 */  or         $a0, $s2, $zero
    /* 5A8268 801EC358 24050018 */  addiu      $a1, $zero, 0x18
    /* 5A826C 801EC35C 0C07B8CC */  jal        func_801EE330_5AA240
    /* 5A8270 801EC360 00003025 */   or        $a2, $zero, $zero
    /* 5A8274 801EC364 10400005 */  beqz       $v0, .L801EC37C_5A828C
    /* 5A8278 801EC368 3C018021 */   lui       $at, %hi(D_8020BA84_5C7994)
    /* 5A827C 801EC36C 24090001 */  addiu      $t1, $zero, 0x1
    /* 5A8280 801EC370 A2290065 */  sb         $t1, 0x65($s1)
    /* 5A8284 801EC374 10000012 */  b          .L801EC3C0_5A82D0
    /* 5A8288 801EC378 92480001 */   lbu       $t0, 0x1($s2)
  .L801EC37C_5A828C:
    /* 5A828C 801EC37C C606001C */  lwc1       $f6, 0x1C($s0)
    /* 5A8290 801EC380 C430BA84 */  lwc1       $f16, %lo(D_8020BA84_5C7994)($at)
    /* 5A8294 801EC384 8E020000 */  lw         $v0, 0x0($s0)
    /* 5A8298 801EC388 46103200 */  add.s      $f8, $f6, $f16
    /* 5A829C 801EC38C E608001C */  swc1       $f8, 0x1C($s0)
    /* 5A82A0 801EC390 C602001C */  lwc1       $f2, 0x1C($s0)
    /* 5A82A4 801EC394 E6020024 */  swc1       $f2, 0x24($s0)
    /* 5A82A8 801EC398 E6020020 */  swc1       $f2, 0x20($s0)
    /* 5A82AC 801EC39C E442001C */  swc1       $f2, 0x1C($v0)
    /* 5A82B0 801EC3A0 E4420020 */  swc1       $f2, 0x20($v0)
    /* 5A82B4 801EC3A4 E4420024 */  swc1       $f2, 0x24($v0)
    /* 5A82B8 801EC3A8 924A0001 */  lbu        $t2, 0x1($s2)
    /* 5A82BC 801EC3AC 254BFFF4 */  addiu      $t3, $t2, -0xC
    /* 5A82C0 801EC3B0 316800FF */  andi       $t0, $t3, 0xFF
    /* 5A82C4 801EC3B4 A2480003 */  sb         $t0, 0x3($s2)
    /* 5A82C8 801EC3B8 A2480002 */  sb         $t0, 0x2($s2)
    /* 5A82CC 801EC3BC A24B0001 */  sb         $t3, 0x1($s2)
  .L801EC3C0_5A82D0:
    /* 5A82D0 801EC3C0 AFA00010 */  sw         $zero, 0x10($sp)
    /* 5A82D4 801EC3C4 AFA00014 */  sw         $zero, 0x14($sp)
    /* 5A82D8 801EC3C8 AFA80018 */  sw         $t0, 0x18($sp)
    /* 5A82DC 801EC3CC 924C0002 */  lbu        $t4, 0x2($s2)
    /* 5A82E0 801EC3D0 3C068020 */  lui        $a2, %hi(D_802049C0_5C08D0)
    /* 5A82E4 801EC3D4 24C649C0 */  addiu      $a2, $a2, %lo(D_802049C0_5C08D0)
    /* 5A82E8 801EC3D8 AFAC001C */  sw         $t4, 0x1C($sp)
    /* 5A82EC 801EC3DC 924D0003 */  lbu        $t5, 0x3($s2)
    /* 5A82F0 801EC3E0 00002025 */  or         $a0, $zero, $zero
    /* 5A82F4 801EC3E4 262500A8 */  addiu      $a1, $s1, 0xA8
    /* 5A82F8 801EC3E8 AFAD0020 */  sw         $t5, 0x20($sp)
    /* 5A82FC 801EC3EC 924E0000 */  lbu        $t6, 0x0($s2)
    /* 5A8300 801EC3F0 00003825 */  or         $a3, $zero, $zero
    /* 5A8304 801EC3F4 0C077155 */  jal        func_801DC554_598464
    /* 5A8308 801EC3F8 AFAE0024 */   sw        $t6, 0x24($sp)
  .L801EC3FC_5A830C:
    /* 5A830C 801EC3FC 8FBF003C */  lw         $ra, 0x3C($sp)
  .L801EC400_5A8310:
    /* 5A8310 801EC400 8FB00030 */  lw         $s0, 0x30($sp)
    /* 5A8314 801EC404 8FB10034 */  lw         $s1, 0x34($sp)
    /* 5A8318 801EC408 8FB20038 */  lw         $s2, 0x38($sp)
    /* 5A831C 801EC40C 03E00008 */  jr         $ra
    /* 5A8320 801EC410 27BD00E0 */   addiu     $sp, $sp, 0xE0
endlabel func_801EBF48_5A7E58
