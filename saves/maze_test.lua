game.create_graph(16, 16, 100.000000, 0.000000, 0.000000)

-- GRAPH NODE ALIASES:
entity_0=0
entity_1=1
entity_2=2
entity_3=3
entity_4=4
entity_5=5
entity_6=6
entity_7=7
entity_8=8
entity_9=9
entity_10=10
entity_11=11
entity_12=12
entity_13=13
entity_14=14
entity_15=15
entity_16=16
entity_17=17
entity_18=18
entity_19=19
entity_20=20
entity_21=21
entity_22=22
entity_23=23
entity_24=24
entity_25=25
entity_26=26
entity_27=27
entity_28=28
entity_29=29
entity_30=30
entity_31=31
entity_32=32
entity_33=33
entity_34=34
entity_35=35
entity_36=36
entity_37=37
entity_38=38
entity_39=39
entity_40=40
entity_41=41
entity_42=42
entity_43=43
entity_44=44
entity_45=45
entity_46=46
entity_47=47
entity_48=48
entity_49=49
entity_50=50
entity_51=51
entity_52=52
entity_53=53
entity_54=54
entity_55=55
entity_56=56
entity_57=57
entity_58=58
entity_59=59
entity_60=60
entity_61=61
entity_62=62
entity_63=63
entity_64=64
entity_65=65
entity_66=66
entity_67=67
entity_68=68
entity_69=69
entity_70=70
entity_71=71
entity_72=72
entity_73=73
entity_74=74
entity_75=75
entity_76=76
entity_77=77
entity_78=78
entity_79=79
entity_80=80
entity_81=81
entity_82=82
entity_83=83
entity_84=84
entity_85=85
entity_86=86
entity_87=87
entity_88=88
entity_89=89
entity_90=90
entity_91=91
entity_92=92
entity_93=93
entity_94=94
entity_95=95
entity_96=96
entity_97=97
entity_98=98
entity_99=99
entity_100=100
entity_101=101
entity_102=102
entity_103=103
entity_104=104
entity_105=105
entity_106=106
entity_107=107
entity_108=108
entity_109=109
entity_110=110
entity_111=111
entity_112=112
entity_113=113
entity_114=114
entity_115=115
entity_116=116
entity_117=117
entity_118=118
entity_119=119
entity_120=120
entity_121=121
entity_122=122
entity_123=123
entity_124=124
entity_125=125
entity_126=126
entity_127=127
entity_128=128
entity_129=129
entity_130=130
entity_131=131
entity_132=132
entity_133=133
entity_134=134
entity_135=135
entity_136=136
entity_137=137
entity_138=138
entity_139=139
entity_140=140
entity_141=141
entity_142=142
entity_143=143
entity_144=144
entity_145=145
entity_146=146
entity_147=147
entity_148=148
entity_149=149
entity_150=150
entity_151=151
entity_152=152
entity_153=153
entity_154=154
entity_155=155
entity_156=156
entity_157=157
entity_158=158
entity_159=159
entity_160=160
entity_161=161
entity_162=162
entity_163=163
entity_164=164
entity_165=165
entity_166=166
entity_167=167
entity_168=168
entity_169=169
entity_170=170
entity_171=171
entity_172=172
entity_173=173
entity_174=174
entity_175=175
entity_176=176
entity_177=177
entity_178=178
entity_179=179
entity_180=180
entity_181=181
entity_182=182
entity_183=183
entity_184=184
entity_185=185
entity_186=186
entity_187=187
entity_188=188
entity_189=189
entity_190=190
entity_191=191
entity_192=192
entity_193=193
entity_194=194
entity_195=195
entity_196=196
entity_197=197
entity_198=198
entity_199=199
entity_200=200
entity_201=201
entity_202=202
entity_203=203
entity_204=204
entity_205=205
entity_206=206
entity_207=207
entity_208=208
entity_209=209
entity_210=210
entity_211=211
entity_212=212
entity_213=213
entity_214=214
entity_215=215
entity_216=216
entity_217=217
entity_218=218
entity_219=219
entity_220=220
entity_221=221
entity_222=222
entity_223=223
entity_224=224
entity_225=225
entity_226=226
entity_227=227
entity_228=228
entity_229=229
entity_230=230
entity_231=231
entity_232=232
entity_233=233
entity_234=234
entity_235=235
entity_236=236
entity_237=237
entity_238=238
entity_239=239
entity_240=240
entity_241=241
entity_242=242
entity_243=243
entity_244=244
entity_245=245
entity_246=246
entity_247=247
entity_248=248
entity_249=249
entity_250=250
entity_251=251
entity_252=252
entity_253=253
entity_254=254
entity_255=255


 -- ENTITIES:
entity_1187 = game.create_entity()
game.add_component(entity_1187, game.enum.component.physics)
game.set_position(entity_1187, 900.000000, 50.000000, 1000.000000)
game.set_solid(entity_1187, true)
game.set_half_height(entity_1187, 50.000000)
game.add_component(entity_1187, game.enum.component.health)
game.buff(entity_1187, 2000)
game.sub_health(entity_1187, 0)
game.add_defense(entity_1187, 13)
game.set_regen(entity_1187, 1)
game.set_alive(entity_1187, true)
game.add_component(entity_1187, game.enum.component.graphics)
game.set_mesh(entity_1187, 'cube.mesh')
game.set_material(entity_1187, 'colour/brown')
game.set_manual_scaling(entity_1187, true)
game.init_graphics_component(entity_1187)
game.set_visible(entity_1187, true)
game.set_scale(entity_1187, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1187, game.enum.component.structure)
entity_1187_residences = { entity_169 }
game.add_residences(entity_1187, 'entity_1187_residences')

entity_1188 = game.create_entity()
game.add_component(entity_1188, game.enum.component.physics)
game.set_position(entity_1188, 800.000000, 50.000000, 1000.000000)
game.set_solid(entity_1188, true)
game.set_half_height(entity_1188, 50.000000)
game.add_component(entity_1188, game.enum.component.health)
game.buff(entity_1188, 2000)
game.sub_health(entity_1188, 0)
game.add_defense(entity_1188, 13)
game.set_regen(entity_1188, 1)
game.set_alive(entity_1188, true)
game.add_component(entity_1188, game.enum.component.graphics)
game.set_mesh(entity_1188, 'cube.mesh')
game.set_material(entity_1188, 'colour/brown')
game.set_manual_scaling(entity_1188, true)
game.init_graphics_component(entity_1188)
game.set_visible(entity_1188, true)
game.set_scale(entity_1188, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1188, game.enum.component.structure)
entity_1188_residences = { entity_168 }
game.add_residences(entity_1188, 'entity_1188_residences')

entity_1189 = game.create_entity()
game.add_component(entity_1189, game.enum.component.physics)
game.set_position(entity_1189, 700.000000, 50.000000, 1000.000000)
game.set_solid(entity_1189, true)
game.set_half_height(entity_1189, 50.000000)
game.add_component(entity_1189, game.enum.component.health)
game.buff(entity_1189, 2000)
game.sub_health(entity_1189, 0)
game.add_defense(entity_1189, 13)
game.set_regen(entity_1189, 1)
game.set_alive(entity_1189, true)
game.add_component(entity_1189, game.enum.component.graphics)
game.set_mesh(entity_1189, 'cube.mesh')
game.set_material(entity_1189, 'colour/brown')
game.set_manual_scaling(entity_1189, true)
game.init_graphics_component(entity_1189)
game.set_visible(entity_1189, true)
game.set_scale(entity_1189, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1189, game.enum.component.structure)
entity_1189_residences = { entity_167 }
game.add_residences(entity_1189, 'entity_1189_residences')

entity_1190 = game.create_entity()
game.add_component(entity_1190, game.enum.component.physics)
game.set_position(entity_1190, 600.000000, 50.000000, 1000.000000)
game.set_solid(entity_1190, true)
game.set_half_height(entity_1190, 50.000000)
game.add_component(entity_1190, game.enum.component.health)
game.buff(entity_1190, 2000)
game.sub_health(entity_1190, 0)
game.add_defense(entity_1190, 13)
game.set_regen(entity_1190, 1)
game.set_alive(entity_1190, true)
game.add_component(entity_1190, game.enum.component.graphics)
game.set_mesh(entity_1190, 'cube.mesh')
game.set_material(entity_1190, 'colour/brown')
game.set_manual_scaling(entity_1190, true)
game.init_graphics_component(entity_1190)
game.set_visible(entity_1190, true)
game.set_scale(entity_1190, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1190, game.enum.component.structure)
entity_1190_residences = { entity_166 }
game.add_residences(entity_1190, 'entity_1190_residences')

entity_1191 = game.create_entity()
game.add_component(entity_1191, game.enum.component.physics)
game.set_position(entity_1191, 500.000000, 50.000000, 1000.000000)
game.set_solid(entity_1191, true)
game.set_half_height(entity_1191, 50.000000)
game.add_component(entity_1191, game.enum.component.health)
game.buff(entity_1191, 2000)
game.sub_health(entity_1191, 0)
game.add_defense(entity_1191, 13)
game.set_regen(entity_1191, 1)
game.set_alive(entity_1191, true)
game.add_component(entity_1191, game.enum.component.graphics)
game.set_mesh(entity_1191, 'cube.mesh')
game.set_material(entity_1191, 'colour/brown')
game.set_manual_scaling(entity_1191, true)
game.init_graphics_component(entity_1191)
game.set_visible(entity_1191, true)
game.set_scale(entity_1191, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1191, game.enum.component.structure)
entity_1191_residences = { entity_165 }
game.add_residences(entity_1191, 'entity_1191_residences')

entity_1192 = game.create_entity()
game.add_component(entity_1192, game.enum.component.physics)
game.set_position(entity_1192, 500.000000, 50.000000, 1100.000000)
game.set_solid(entity_1192, true)
game.set_half_height(entity_1192, 50.000000)
game.add_component(entity_1192, game.enum.component.health)
game.buff(entity_1192, 2000)
game.sub_health(entity_1192, 0)
game.add_defense(entity_1192, 13)
game.set_regen(entity_1192, 1)
game.set_alive(entity_1192, true)
game.add_component(entity_1192, game.enum.component.graphics)
game.set_mesh(entity_1192, 'cube.mesh')
game.set_material(entity_1192, 'colour/brown')
game.set_manual_scaling(entity_1192, true)
game.init_graphics_component(entity_1192)
game.set_visible(entity_1192, true)
game.set_scale(entity_1192, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1192, game.enum.component.structure)
entity_1192_residences = { entity_181 }
game.add_residences(entity_1192, 'entity_1192_residences')

entity_1193 = game.create_entity()
game.add_component(entity_1193, game.enum.component.physics)
game.set_position(entity_1193, 500.000000, 50.000000, 1200.000000)
game.set_solid(entity_1193, true)
game.set_half_height(entity_1193, 50.000000)
game.add_component(entity_1193, game.enum.component.health)
game.buff(entity_1193, 2000)
game.sub_health(entity_1193, 0)
game.add_defense(entity_1193, 13)
game.set_regen(entity_1193, 1)
game.set_alive(entity_1193, true)
game.add_component(entity_1193, game.enum.component.graphics)
game.set_mesh(entity_1193, 'cube.mesh')
game.set_material(entity_1193, 'colour/brown')
game.set_manual_scaling(entity_1193, true)
game.init_graphics_component(entity_1193)
game.set_visible(entity_1193, true)
game.set_scale(entity_1193, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1193, game.enum.component.structure)
entity_1193_residences = { entity_197 }
game.add_residences(entity_1193, 'entity_1193_residences')

entity_1194 = game.create_entity()
game.add_component(entity_1194, game.enum.component.physics)
game.set_position(entity_1194, 500.000000, 50.000000, 1300.000000)
game.set_solid(entity_1194, true)
game.set_half_height(entity_1194, 50.000000)
game.add_component(entity_1194, game.enum.component.health)
game.buff(entity_1194, 2000)
game.sub_health(entity_1194, 0)
game.add_defense(entity_1194, 13)
game.set_regen(entity_1194, 1)
game.set_alive(entity_1194, true)
game.add_component(entity_1194, game.enum.component.graphics)
game.set_mesh(entity_1194, 'cube.mesh')
game.set_material(entity_1194, 'colour/brown')
game.set_manual_scaling(entity_1194, true)
game.init_graphics_component(entity_1194)
game.set_visible(entity_1194, true)
game.set_scale(entity_1194, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1194, game.enum.component.structure)
entity_1194_residences = { entity_213 }
game.add_residences(entity_1194, 'entity_1194_residences')

entity_1195 = game.create_entity()
game.add_component(entity_1195, game.enum.component.physics)
game.set_position(entity_1195, 900.000000, 50.000000, 1100.000000)
game.set_solid(entity_1195, true)
game.set_half_height(entity_1195, 50.000000)
game.add_component(entity_1195, game.enum.component.health)
game.buff(entity_1195, 2000)
game.sub_health(entity_1195, 0)
game.add_defense(entity_1195, 13)
game.set_regen(entity_1195, 1)
game.set_alive(entity_1195, true)
game.add_component(entity_1195, game.enum.component.graphics)
game.set_mesh(entity_1195, 'cube.mesh')
game.set_material(entity_1195, 'colour/brown')
game.set_manual_scaling(entity_1195, true)
game.init_graphics_component(entity_1195)
game.set_visible(entity_1195, true)
game.set_scale(entity_1195, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1195, game.enum.component.structure)
entity_1195_residences = { entity_185 }
game.add_residences(entity_1195, 'entity_1195_residences')

entity_1196 = game.create_entity()
game.add_component(entity_1196, game.enum.component.physics)
game.set_position(entity_1196, 900.000000, 50.000000, 1200.000000)
game.set_solid(entity_1196, true)
game.set_half_height(entity_1196, 50.000000)
game.add_component(entity_1196, game.enum.component.health)
game.buff(entity_1196, 2000)
game.sub_health(entity_1196, 0)
game.add_defense(entity_1196, 13)
game.set_regen(entity_1196, 1)
game.set_alive(entity_1196, true)
game.add_component(entity_1196, game.enum.component.graphics)
game.set_mesh(entity_1196, 'cube.mesh')
game.set_material(entity_1196, 'colour/brown')
game.set_manual_scaling(entity_1196, true)
game.init_graphics_component(entity_1196)
game.set_visible(entity_1196, true)
game.set_scale(entity_1196, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1196, game.enum.component.structure)
entity_1196_residences = { entity_201 }
game.add_residences(entity_1196, 'entity_1196_residences')

entity_1197 = game.create_entity()
game.add_component(entity_1197, game.enum.component.physics)
game.set_position(entity_1197, 900.000000, 50.000000, 1300.000000)
game.set_solid(entity_1197, true)
game.set_half_height(entity_1197, 50.000000)
game.add_component(entity_1197, game.enum.component.health)
game.buff(entity_1197, 2000)
game.sub_health(entity_1197, 0)
game.add_defense(entity_1197, 13)
game.set_regen(entity_1197, 1)
game.set_alive(entity_1197, true)
game.add_component(entity_1197, game.enum.component.graphics)
game.set_mesh(entity_1197, 'cube.mesh')
game.set_material(entity_1197, 'colour/brown')
game.set_manual_scaling(entity_1197, true)
game.init_graphics_component(entity_1197)
game.set_visible(entity_1197, true)
game.set_scale(entity_1197, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1197, game.enum.component.structure)
entity_1197_residences = { entity_217 }
game.add_residences(entity_1197, 'entity_1197_residences')

entity_1198 = game.create_entity()
game.add_component(entity_1198, game.enum.component.physics)
game.set_position(entity_1198, 900.000000, 50.000000, 1500.000000)
game.set_solid(entity_1198, true)
game.set_half_height(entity_1198, 50.000000)
game.add_component(entity_1198, game.enum.component.health)
game.buff(entity_1198, 2000)
game.sub_health(entity_1198, 0)
game.add_defense(entity_1198, 13)
game.set_regen(entity_1198, 1)
game.set_alive(entity_1198, true)
game.add_component(entity_1198, game.enum.component.graphics)
game.set_mesh(entity_1198, 'cube.mesh')
game.set_material(entity_1198, 'colour/brown')
game.set_manual_scaling(entity_1198, true)
game.init_graphics_component(entity_1198)
game.set_visible(entity_1198, true)
game.set_scale(entity_1198, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1198, game.enum.component.structure)
entity_1198_residences = { entity_249 }
game.add_residences(entity_1198, 'entity_1198_residences')

entity_1199 = game.create_entity()
game.add_component(entity_1199, game.enum.component.physics)
game.set_position(entity_1199, 800.000000, 50.000000, 1500.000000)
game.set_solid(entity_1199, true)
game.set_half_height(entity_1199, 50.000000)
game.add_component(entity_1199, game.enum.component.health)
game.buff(entity_1199, 2000)
game.sub_health(entity_1199, 0)
game.add_defense(entity_1199, 13)
game.set_regen(entity_1199, 1)
game.set_alive(entity_1199, true)
game.add_component(entity_1199, game.enum.component.graphics)
game.set_mesh(entity_1199, 'cube.mesh')
game.set_material(entity_1199, 'colour/brown')
game.set_manual_scaling(entity_1199, true)
game.init_graphics_component(entity_1199)
game.set_visible(entity_1199, true)
game.set_scale(entity_1199, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1199, game.enum.component.structure)
entity_1199_residences = { entity_248 }
game.add_residences(entity_1199, 'entity_1199_residences')

entity_1200 = game.create_entity()
game.add_component(entity_1200, game.enum.component.physics)
game.set_position(entity_1200, 700.000000, 50.000000, 1500.000000)
game.set_solid(entity_1200, true)
game.set_half_height(entity_1200, 50.000000)
game.add_component(entity_1200, game.enum.component.health)
game.buff(entity_1200, 2000)
game.sub_health(entity_1200, 0)
game.add_defense(entity_1200, 13)
game.set_regen(entity_1200, 1)
game.set_alive(entity_1200, true)
game.add_component(entity_1200, game.enum.component.graphics)
game.set_mesh(entity_1200, 'cube.mesh')
game.set_material(entity_1200, 'colour/brown')
game.set_manual_scaling(entity_1200, true)
game.init_graphics_component(entity_1200)
game.set_visible(entity_1200, true)
game.set_scale(entity_1200, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1200, game.enum.component.structure)
entity_1200_residences = { entity_247 }
game.add_residences(entity_1200, 'entity_1200_residences')

entity_1201 = game.create_entity()
game.add_component(entity_1201, game.enum.component.physics)
game.set_position(entity_1201, 600.000000, 50.000000, 1500.000000)
game.set_solid(entity_1201, true)
game.set_half_height(entity_1201, 50.000000)
game.add_component(entity_1201, game.enum.component.health)
game.buff(entity_1201, 2000)
game.sub_health(entity_1201, 0)
game.add_defense(entity_1201, 13)
game.set_regen(entity_1201, 1)
game.set_alive(entity_1201, true)
game.add_component(entity_1201, game.enum.component.graphics)
game.set_mesh(entity_1201, 'cube.mesh')
game.set_material(entity_1201, 'colour/brown')
game.set_manual_scaling(entity_1201, true)
game.init_graphics_component(entity_1201)
game.set_visible(entity_1201, true)
game.set_scale(entity_1201, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1201, game.enum.component.structure)
entity_1201_residences = { entity_246 }
game.add_residences(entity_1201, 'entity_1201_residences')

entity_1202 = game.create_entity()
game.add_component(entity_1202, game.enum.component.physics)
game.set_position(entity_1202, 500.000000, 50.000000, 1500.000000)
game.set_solid(entity_1202, true)
game.set_half_height(entity_1202, 50.000000)
game.add_component(entity_1202, game.enum.component.health)
game.buff(entity_1202, 2000)
game.sub_health(entity_1202, 0)
game.add_defense(entity_1202, 13)
game.set_regen(entity_1202, 1)
game.set_alive(entity_1202, true)
game.add_component(entity_1202, game.enum.component.graphics)
game.set_mesh(entity_1202, 'cube.mesh')
game.set_material(entity_1202, 'colour/brown')
game.set_manual_scaling(entity_1202, true)
game.init_graphics_component(entity_1202)
game.set_visible(entity_1202, true)
game.set_scale(entity_1202, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1202, game.enum.component.structure)
entity_1202_residences = { entity_245 }
game.add_residences(entity_1202, 'entity_1202_residences')

entity_1203 = game.create_entity()
game.add_component(entity_1203, game.enum.component.physics)
game.set_position(entity_1203, 400.000000, 50.000000, 1000.000000)
game.set_solid(entity_1203, true)
game.set_half_height(entity_1203, 50.000000)
game.add_component(entity_1203, game.enum.component.health)
game.buff(entity_1203, 2000)
game.sub_health(entity_1203, 0)
game.add_defense(entity_1203, 13)
game.set_regen(entity_1203, 1)
game.set_alive(entity_1203, true)
game.add_component(entity_1203, game.enum.component.graphics)
game.set_mesh(entity_1203, 'cube.mesh')
game.set_material(entity_1203, 'colour/brown')
game.set_manual_scaling(entity_1203, true)
game.init_graphics_component(entity_1203)
game.set_visible(entity_1203, true)
game.set_scale(entity_1203, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1203, game.enum.component.structure)
entity_1203_residences = { entity_164 }
game.add_residences(entity_1203, 'entity_1203_residences')

entity_1204 = game.create_entity()
game.add_component(entity_1204, game.enum.component.physics)
game.set_position(entity_1204, 300.000000, 50.000000, 1000.000000)
game.set_solid(entity_1204, true)
game.set_half_height(entity_1204, 50.000000)
game.add_component(entity_1204, game.enum.component.health)
game.buff(entity_1204, 2000)
game.sub_health(entity_1204, 0)
game.add_defense(entity_1204, 13)
game.set_regen(entity_1204, 1)
game.set_alive(entity_1204, true)
game.add_component(entity_1204, game.enum.component.graphics)
game.set_mesh(entity_1204, 'cube.mesh')
game.set_material(entity_1204, 'colour/brown')
game.set_manual_scaling(entity_1204, true)
game.init_graphics_component(entity_1204)
game.set_visible(entity_1204, true)
game.set_scale(entity_1204, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1204, game.enum.component.structure)
entity_1204_residences = { entity_163 }
game.add_residences(entity_1204, 'entity_1204_residences')

entity_1205 = game.create_entity()
game.add_component(entity_1205, game.enum.component.physics)
game.set_position(entity_1205, 100.000000, 50.000000, 1000.000000)
game.set_solid(entity_1205, true)
game.set_half_height(entity_1205, 50.000000)
game.add_component(entity_1205, game.enum.component.health)
game.buff(entity_1205, 2000)
game.sub_health(entity_1205, 0)
game.add_defense(entity_1205, 13)
game.set_regen(entity_1205, 1)
game.set_alive(entity_1205, true)
game.add_component(entity_1205, game.enum.component.graphics)
game.set_mesh(entity_1205, 'cube.mesh')
game.set_material(entity_1205, 'colour/brown')
game.set_manual_scaling(entity_1205, true)
game.init_graphics_component(entity_1205)
game.set_visible(entity_1205, true)
game.set_scale(entity_1205, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1205, game.enum.component.structure)
entity_1205_residences = { entity_161 }
game.add_residences(entity_1205, 'entity_1205_residences')

entity_1206 = game.create_entity()
game.add_component(entity_1206, game.enum.component.physics)
game.set_position(entity_1206, 0.000000, 50.000000, 1000.000000)
game.set_solid(entity_1206, true)
game.set_half_height(entity_1206, 50.000000)
game.add_component(entity_1206, game.enum.component.health)
game.buff(entity_1206, 2000)
game.sub_health(entity_1206, 0)
game.add_defense(entity_1206, 13)
game.set_regen(entity_1206, 1)
game.set_alive(entity_1206, true)
game.add_component(entity_1206, game.enum.component.graphics)
game.set_mesh(entity_1206, 'cube.mesh')
game.set_material(entity_1206, 'colour/brown')
game.set_manual_scaling(entity_1206, true)
game.init_graphics_component(entity_1206)
game.set_visible(entity_1206, true)
game.set_scale(entity_1206, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1206, game.enum.component.structure)
entity_1206_residences = { entity_160 }
game.add_residences(entity_1206, 'entity_1206_residences')

entity_1207 = game.create_entity()
game.add_component(entity_1207, game.enum.component.physics)
game.set_position(entity_1207, 100.000000, 50.000000, 1200.000000)
game.set_solid(entity_1207, true)
game.set_half_height(entity_1207, 50.000000)
game.add_component(entity_1207, game.enum.component.health)
game.buff(entity_1207, 2000)
game.sub_health(entity_1207, 0)
game.add_defense(entity_1207, 13)
game.set_regen(entity_1207, 1)
game.set_alive(entity_1207, true)
game.add_component(entity_1207, game.enum.component.graphics)
game.set_mesh(entity_1207, 'cube.mesh')
game.set_material(entity_1207, 'colour/brown')
game.set_manual_scaling(entity_1207, true)
game.init_graphics_component(entity_1207)
game.set_visible(entity_1207, true)
game.set_scale(entity_1207, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1207, game.enum.component.structure)
entity_1207_residences = { entity_193 }
game.add_residences(entity_1207, 'entity_1207_residences')

entity_1208 = game.create_entity()
game.add_component(entity_1208, game.enum.component.physics)
game.set_position(entity_1208, 200.000000, 50.000000, 1200.000000)
game.set_solid(entity_1208, true)
game.set_half_height(entity_1208, 50.000000)
game.add_component(entity_1208, game.enum.component.health)
game.buff(entity_1208, 2000)
game.sub_health(entity_1208, 0)
game.add_defense(entity_1208, 13)
game.set_regen(entity_1208, 1)
game.set_alive(entity_1208, true)
game.add_component(entity_1208, game.enum.component.graphics)
game.set_mesh(entity_1208, 'cube.mesh')
game.set_material(entity_1208, 'colour/brown')
game.set_manual_scaling(entity_1208, true)
game.init_graphics_component(entity_1208)
game.set_visible(entity_1208, true)
game.set_scale(entity_1208, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1208, game.enum.component.structure)
entity_1208_residences = { entity_194 }
game.add_residences(entity_1208, 'entity_1208_residences')

entity_1209 = game.create_entity()
game.add_component(entity_1209, game.enum.component.physics)
game.set_position(entity_1209, 300.000000, 50.000000, 1200.000000)
game.set_solid(entity_1209, true)
game.set_half_height(entity_1209, 50.000000)
game.add_component(entity_1209, game.enum.component.health)
game.buff(entity_1209, 2000)
game.sub_health(entity_1209, 0)
game.add_defense(entity_1209, 13)
game.set_regen(entity_1209, 1)
game.set_alive(entity_1209, true)
game.add_component(entity_1209, game.enum.component.graphics)
game.set_mesh(entity_1209, 'cube.mesh')
game.set_material(entity_1209, 'colour/brown')
game.set_manual_scaling(entity_1209, true)
game.init_graphics_component(entity_1209)
game.set_visible(entity_1209, true)
game.set_scale(entity_1209, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1209, game.enum.component.structure)
entity_1209_residences = { entity_195 }
game.add_residences(entity_1209, 'entity_1209_residences')

entity_1210 = game.create_entity()
game.add_component(entity_1210, game.enum.component.physics)
game.set_position(entity_1210, 600.000000, 50.000000, 1400.000000)
game.set_solid(entity_1210, true)
game.set_half_height(entity_1210, 50.000000)
game.add_component(entity_1210, game.enum.component.health)
game.buff(entity_1210, 2000)
game.sub_health(entity_1210, 0)
game.add_defense(entity_1210, 13)
game.set_regen(entity_1210, 1)
game.set_alive(entity_1210, true)
game.add_component(entity_1210, game.enum.component.graphics)
game.set_mesh(entity_1210, 'cube.mesh')
game.set_material(entity_1210, 'colour/brown')
game.set_manual_scaling(entity_1210, true)
game.init_graphics_component(entity_1210)
game.set_visible(entity_1210, true)
game.set_scale(entity_1210, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1210, game.enum.component.structure)
entity_1210_residences = { entity_230 }
game.add_residences(entity_1210, 'entity_1210_residences')

entity_1211 = game.create_entity()
game.add_component(entity_1211, game.enum.component.physics)
game.set_position(entity_1211, 300.000000, 50.000000, 1300.000000)
game.set_solid(entity_1211, true)
game.set_half_height(entity_1211, 50.000000)
game.add_component(entity_1211, game.enum.component.health)
game.buff(entity_1211, 2000)
game.sub_health(entity_1211, 0)
game.add_defense(entity_1211, 13)
game.set_regen(entity_1211, 1)
game.set_alive(entity_1211, true)
game.add_component(entity_1211, game.enum.component.graphics)
game.set_mesh(entity_1211, 'cube.mesh')
game.set_material(entity_1211, 'colour/brown')
game.set_manual_scaling(entity_1211, true)
game.init_graphics_component(entity_1211)
game.set_visible(entity_1211, true)
game.set_scale(entity_1211, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1211, game.enum.component.structure)
entity_1211_residences = { entity_211 }
game.add_residences(entity_1211, 'entity_1211_residences')

entity_1212 = game.create_entity()
game.add_component(entity_1212, game.enum.component.physics)
game.set_position(entity_1212, 300.000000, 50.000000, 1400.000000)
game.set_solid(entity_1212, true)
game.set_half_height(entity_1212, 50.000000)
game.add_component(entity_1212, game.enum.component.health)
game.buff(entity_1212, 2000)
game.sub_health(entity_1212, 0)
game.add_defense(entity_1212, 13)
game.set_regen(entity_1212, 1)
game.set_alive(entity_1212, true)
game.add_component(entity_1212, game.enum.component.graphics)
game.set_mesh(entity_1212, 'cube.mesh')
game.set_material(entity_1212, 'colour/brown')
game.set_manual_scaling(entity_1212, true)
game.init_graphics_component(entity_1212)
game.set_visible(entity_1212, true)
game.set_scale(entity_1212, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1212, game.enum.component.structure)
entity_1212_residences = { entity_227 }
game.add_residences(entity_1212, 'entity_1212_residences')

entity_1213 = game.create_entity()
game.add_component(entity_1213, game.enum.component.physics)
game.set_position(entity_1213, 100.000000, 50.000000, 1300.000000)
game.set_solid(entity_1213, true)
game.set_half_height(entity_1213, 50.000000)
game.add_component(entity_1213, game.enum.component.health)
game.buff(entity_1213, 2000)
game.sub_health(entity_1213, 0)
game.add_defense(entity_1213, 13)
game.set_regen(entity_1213, 1)
game.set_alive(entity_1213, true)
game.add_component(entity_1213, game.enum.component.graphics)
game.set_mesh(entity_1213, 'cube.mesh')
game.set_material(entity_1213, 'colour/brown')
game.set_manual_scaling(entity_1213, true)
game.init_graphics_component(entity_1213)
game.set_visible(entity_1213, true)
game.set_scale(entity_1213, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1213, game.enum.component.structure)
entity_1213_residences = { entity_209 }
game.add_residences(entity_1213, 'entity_1213_residences')

entity_1214 = game.create_entity()
game.add_component(entity_1214, game.enum.component.physics)
game.set_position(entity_1214, 100.000000, 50.000000, 1400.000000)
game.set_solid(entity_1214, true)
game.set_half_height(entity_1214, 50.000000)
game.add_component(entity_1214, game.enum.component.health)
game.buff(entity_1214, 2000)
game.sub_health(entity_1214, 0)
game.add_defense(entity_1214, 13)
game.set_regen(entity_1214, 1)
game.set_alive(entity_1214, true)
game.add_component(entity_1214, game.enum.component.graphics)
game.set_mesh(entity_1214, 'cube.mesh')
game.set_material(entity_1214, 'colour/brown')
game.set_manual_scaling(entity_1214, true)
game.init_graphics_component(entity_1214)
game.set_visible(entity_1214, true)
game.set_scale(entity_1214, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1214, game.enum.component.structure)
entity_1214_residences = { entity_225 }
game.add_residences(entity_1214, 'entity_1214_residences')

entity_1215 = game.create_entity()
game.add_component(entity_1215, game.enum.component.physics)
game.set_position(entity_1215, 1000.000000, 50.000000, 1000.000000)
game.set_solid(entity_1215, true)
game.set_half_height(entity_1215, 50.000000)
game.add_component(entity_1215, game.enum.component.health)
game.buff(entity_1215, 2000)
game.sub_health(entity_1215, 0)
game.add_defense(entity_1215, 13)
game.set_regen(entity_1215, 1)
game.set_alive(entity_1215, true)
game.add_component(entity_1215, game.enum.component.graphics)
game.set_mesh(entity_1215, 'cube.mesh')
game.set_material(entity_1215, 'colour/brown')
game.set_manual_scaling(entity_1215, true)
game.init_graphics_component(entity_1215)
game.set_visible(entity_1215, true)
game.set_scale(entity_1215, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1215, game.enum.component.structure)
entity_1215_residences = { entity_170 }
game.add_residences(entity_1215, 'entity_1215_residences')

entity_1216 = game.create_entity()
game.add_component(entity_1216, game.enum.component.physics)
game.set_position(entity_1216, 1100.000000, 50.000000, 1000.000000)
game.set_solid(entity_1216, true)
game.set_half_height(entity_1216, 50.000000)
game.add_component(entity_1216, game.enum.component.health)
game.buff(entity_1216, 2000)
game.sub_health(entity_1216, 0)
game.add_defense(entity_1216, 13)
game.set_regen(entity_1216, 1)
game.set_alive(entity_1216, true)
game.add_component(entity_1216, game.enum.component.graphics)
game.set_mesh(entity_1216, 'cube.mesh')
game.set_material(entity_1216, 'colour/brown')
game.set_manual_scaling(entity_1216, true)
game.init_graphics_component(entity_1216)
game.set_visible(entity_1216, true)
game.set_scale(entity_1216, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1216, game.enum.component.structure)
entity_1216_residences = { entity_171 }
game.add_residences(entity_1216, 'entity_1216_residences')

entity_1217 = game.create_entity()
game.add_component(entity_1217, game.enum.component.physics)
game.set_position(entity_1217, 1100.000000, 50.000000, 900.000000)
game.set_solid(entity_1217, true)
game.set_half_height(entity_1217, 50.000000)
game.add_component(entity_1217, game.enum.component.health)
game.buff(entity_1217, 2000)
game.sub_health(entity_1217, 0)
game.add_defense(entity_1217, 13)
game.set_regen(entity_1217, 1)
game.set_alive(entity_1217, true)
game.add_component(entity_1217, game.enum.component.graphics)
game.set_mesh(entity_1217, 'cube.mesh')
game.set_material(entity_1217, 'colour/brown')
game.set_manual_scaling(entity_1217, true)
game.init_graphics_component(entity_1217)
game.set_visible(entity_1217, true)
game.set_scale(entity_1217, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1217, game.enum.component.structure)
entity_1217_residences = { entity_155 }
game.add_residences(entity_1217, 'entity_1217_residences')

entity_1218 = game.create_entity()
game.add_component(entity_1218, game.enum.component.physics)
game.set_position(entity_1218, 1100.000000, 50.000000, 800.000000)
game.set_solid(entity_1218, true)
game.set_half_height(entity_1218, 50.000000)
game.add_component(entity_1218, game.enum.component.health)
game.buff(entity_1218, 2000)
game.sub_health(entity_1218, 0)
game.add_defense(entity_1218, 13)
game.set_regen(entity_1218, 1)
game.set_alive(entity_1218, true)
game.add_component(entity_1218, game.enum.component.graphics)
game.set_mesh(entity_1218, 'cube.mesh')
game.set_material(entity_1218, 'colour/brown')
game.set_manual_scaling(entity_1218, true)
game.init_graphics_component(entity_1218)
game.set_visible(entity_1218, true)
game.set_scale(entity_1218, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1218, game.enum.component.structure)
entity_1218_residences = { entity_139 }
game.add_residences(entity_1218, 'entity_1218_residences')

entity_1219 = game.create_entity()
game.add_component(entity_1219, game.enum.component.physics)
game.set_position(entity_1219, 1100.000000, 50.000000, 700.000000)
game.set_solid(entity_1219, true)
game.set_half_height(entity_1219, 50.000000)
game.add_component(entity_1219, game.enum.component.health)
game.buff(entity_1219, 2000)
game.sub_health(entity_1219, 0)
game.add_defense(entity_1219, 13)
game.set_regen(entity_1219, 1)
game.set_alive(entity_1219, true)
game.add_component(entity_1219, game.enum.component.graphics)
game.set_mesh(entity_1219, 'cube.mesh')
game.set_material(entity_1219, 'colour/brown')
game.set_manual_scaling(entity_1219, true)
game.init_graphics_component(entity_1219)
game.set_visible(entity_1219, true)
game.set_scale(entity_1219, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1219, game.enum.component.structure)
entity_1219_residences = { entity_123 }
game.add_residences(entity_1219, 'entity_1219_residences')

entity_1220 = game.create_entity()
game.add_component(entity_1220, game.enum.component.physics)
game.set_position(entity_1220, 1100.000000, 50.000000, 600.000000)
game.set_solid(entity_1220, true)
game.set_half_height(entity_1220, 50.000000)
game.add_component(entity_1220, game.enum.component.health)
game.buff(entity_1220, 2000)
game.sub_health(entity_1220, 0)
game.add_defense(entity_1220, 13)
game.set_regen(entity_1220, 1)
game.set_alive(entity_1220, true)
game.add_component(entity_1220, game.enum.component.graphics)
game.set_mesh(entity_1220, 'cube.mesh')
game.set_material(entity_1220, 'colour/brown')
game.set_manual_scaling(entity_1220, true)
game.init_graphics_component(entity_1220)
game.set_visible(entity_1220, true)
game.set_scale(entity_1220, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1220, game.enum.component.structure)
entity_1220_residences = { entity_107 }
game.add_residences(entity_1220, 'entity_1220_residences')

entity_1221 = game.create_entity()
game.add_component(entity_1221, game.enum.component.physics)
game.set_position(entity_1221, 1100.000000, 50.000000, 500.000000)
game.set_solid(entity_1221, true)
game.set_half_height(entity_1221, 50.000000)
game.add_component(entity_1221, game.enum.component.health)
game.buff(entity_1221, 2000)
game.sub_health(entity_1221, 0)
game.add_defense(entity_1221, 13)
game.set_regen(entity_1221, 1)
game.set_alive(entity_1221, true)
game.add_component(entity_1221, game.enum.component.graphics)
game.set_mesh(entity_1221, 'cube.mesh')
game.set_material(entity_1221, 'colour/brown')
game.set_manual_scaling(entity_1221, true)
game.init_graphics_component(entity_1221)
game.set_visible(entity_1221, true)
game.set_scale(entity_1221, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1221, game.enum.component.structure)
entity_1221_residences = { entity_91 }
game.add_residences(entity_1221, 'entity_1221_residences')

entity_1222 = game.create_entity()
game.add_component(entity_1222, game.enum.component.physics)
game.set_position(entity_1222, 1100.000000, 50.000000, 400.000000)
game.set_solid(entity_1222, true)
game.set_half_height(entity_1222, 50.000000)
game.add_component(entity_1222, game.enum.component.health)
game.buff(entity_1222, 2000)
game.sub_health(entity_1222, 0)
game.add_defense(entity_1222, 13)
game.set_regen(entity_1222, 1)
game.set_alive(entity_1222, true)
game.add_component(entity_1222, game.enum.component.graphics)
game.set_mesh(entity_1222, 'cube.mesh')
game.set_material(entity_1222, 'colour/brown')
game.set_manual_scaling(entity_1222, true)
game.init_graphics_component(entity_1222)
game.set_visible(entity_1222, true)
game.set_scale(entity_1222, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1222, game.enum.component.structure)
entity_1222_residences = { entity_75 }
game.add_residences(entity_1222, 'entity_1222_residences')

entity_1223 = game.create_entity()
game.add_component(entity_1223, game.enum.component.physics)
game.set_position(entity_1223, 1000.000000, 50.000000, 500.000000)
game.set_solid(entity_1223, true)
game.set_half_height(entity_1223, 50.000000)
game.add_component(entity_1223, game.enum.component.health)
game.buff(entity_1223, 2000)
game.sub_health(entity_1223, 0)
game.add_defense(entity_1223, 13)
game.set_regen(entity_1223, 1)
game.set_alive(entity_1223, true)
game.add_component(entity_1223, game.enum.component.graphics)
game.set_mesh(entity_1223, 'cube.mesh')
game.set_material(entity_1223, 'colour/brown')
game.set_manual_scaling(entity_1223, true)
game.init_graphics_component(entity_1223)
game.set_visible(entity_1223, true)
game.set_scale(entity_1223, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1223, game.enum.component.structure)
entity_1223_residences = { entity_90 }
game.add_residences(entity_1223, 'entity_1223_residences')

entity_1224 = game.create_entity()
game.add_component(entity_1224, game.enum.component.physics)
game.set_position(entity_1224, 900.000000, 50.000000, 500.000000)
game.set_solid(entity_1224, true)
game.set_half_height(entity_1224, 50.000000)
game.add_component(entity_1224, game.enum.component.health)
game.buff(entity_1224, 2000)
game.sub_health(entity_1224, 0)
game.add_defense(entity_1224, 13)
game.set_regen(entity_1224, 1)
game.set_alive(entity_1224, true)
game.add_component(entity_1224, game.enum.component.graphics)
game.set_mesh(entity_1224, 'cube.mesh')
game.set_material(entity_1224, 'colour/brown')
game.set_manual_scaling(entity_1224, true)
game.init_graphics_component(entity_1224)
game.set_visible(entity_1224, true)
game.set_scale(entity_1224, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1224, game.enum.component.structure)
entity_1224_residences = { entity_89 }
game.add_residences(entity_1224, 'entity_1224_residences')

entity_1225 = game.create_entity()
game.add_component(entity_1225, game.enum.component.physics)
game.set_position(entity_1225, 800.000000, 50.000000, 500.000000)
game.set_solid(entity_1225, true)
game.set_half_height(entity_1225, 50.000000)
game.add_component(entity_1225, game.enum.component.health)
game.buff(entity_1225, 2000)
game.sub_health(entity_1225, 0)
game.add_defense(entity_1225, 13)
game.set_regen(entity_1225, 1)
game.set_alive(entity_1225, true)
game.add_component(entity_1225, game.enum.component.graphics)
game.set_mesh(entity_1225, 'cube.mesh')
game.set_material(entity_1225, 'colour/brown')
game.set_manual_scaling(entity_1225, true)
game.init_graphics_component(entity_1225)
game.set_visible(entity_1225, true)
game.set_scale(entity_1225, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1225, game.enum.component.structure)
entity_1225_residences = { entity_88 }
game.add_residences(entity_1225, 'entity_1225_residences')

entity_1226 = game.create_entity()
game.add_component(entity_1226, game.enum.component.physics)
game.set_position(entity_1226, 800.000000, 50.000000, 400.000000)
game.set_solid(entity_1226, true)
game.set_half_height(entity_1226, 50.000000)
game.add_component(entity_1226, game.enum.component.health)
game.buff(entity_1226, 2000)
game.sub_health(entity_1226, 0)
game.add_defense(entity_1226, 13)
game.set_regen(entity_1226, 1)
game.set_alive(entity_1226, true)
game.add_component(entity_1226, game.enum.component.graphics)
game.set_mesh(entity_1226, 'cube.mesh')
game.set_material(entity_1226, 'colour/brown')
game.set_manual_scaling(entity_1226, true)
game.init_graphics_component(entity_1226)
game.set_visible(entity_1226, true)
game.set_scale(entity_1226, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1226, game.enum.component.structure)
entity_1226_residences = { entity_72 }
game.add_residences(entity_1226, 'entity_1226_residences')

entity_1227 = game.create_entity()
game.add_component(entity_1227, game.enum.component.physics)
game.set_position(entity_1227, 800.000000, 50.000000, 300.000000)
game.set_solid(entity_1227, true)
game.set_half_height(entity_1227, 50.000000)
game.add_component(entity_1227, game.enum.component.health)
game.buff(entity_1227, 2000)
game.sub_health(entity_1227, 0)
game.add_defense(entity_1227, 13)
game.set_regen(entity_1227, 1)
game.set_alive(entity_1227, true)
game.add_component(entity_1227, game.enum.component.graphics)
game.set_mesh(entity_1227, 'cube.mesh')
game.set_material(entity_1227, 'colour/brown')
game.set_manual_scaling(entity_1227, true)
game.init_graphics_component(entity_1227)
game.set_visible(entity_1227, true)
game.set_scale(entity_1227, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1227, game.enum.component.structure)
entity_1227_residences = { entity_56 }
game.add_residences(entity_1227, 'entity_1227_residences')

entity_1228 = game.create_entity()
game.add_component(entity_1228, game.enum.component.physics)
game.set_position(entity_1228, 800.000000, 50.000000, 200.000000)
game.set_solid(entity_1228, true)
game.set_half_height(entity_1228, 50.000000)
game.add_component(entity_1228, game.enum.component.health)
game.buff(entity_1228, 2000)
game.sub_health(entity_1228, 0)
game.add_defense(entity_1228, 13)
game.set_regen(entity_1228, 1)
game.set_alive(entity_1228, true)
game.add_component(entity_1228, game.enum.component.graphics)
game.set_mesh(entity_1228, 'cube.mesh')
game.set_material(entity_1228, 'colour/brown')
game.set_manual_scaling(entity_1228, true)
game.init_graphics_component(entity_1228)
game.set_visible(entity_1228, true)
game.set_scale(entity_1228, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1228, game.enum.component.structure)
entity_1228_residences = { entity_40 }
game.add_residences(entity_1228, 'entity_1228_residences')

entity_1229 = game.create_entity()
game.add_component(entity_1229, game.enum.component.physics)
game.set_position(entity_1229, 900.000000, 50.000000, 200.000000)
game.set_solid(entity_1229, true)
game.set_half_height(entity_1229, 50.000000)
game.add_component(entity_1229, game.enum.component.health)
game.buff(entity_1229, 2000)
game.sub_health(entity_1229, 0)
game.add_defense(entity_1229, 13)
game.set_regen(entity_1229, 1)
game.set_alive(entity_1229, true)
game.add_component(entity_1229, game.enum.component.graphics)
game.set_mesh(entity_1229, 'cube.mesh')
game.set_material(entity_1229, 'colour/brown')
game.set_manual_scaling(entity_1229, true)
game.init_graphics_component(entity_1229)
game.set_visible(entity_1229, true)
game.set_scale(entity_1229, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1229, game.enum.component.structure)
entity_1229_residences = { entity_41 }
game.add_residences(entity_1229, 'entity_1229_residences')

entity_1230 = game.create_entity()
game.add_component(entity_1230, game.enum.component.physics)
game.set_position(entity_1230, 900.000000, 50.000000, 100.000000)
game.set_solid(entity_1230, true)
game.set_half_height(entity_1230, 50.000000)
game.add_component(entity_1230, game.enum.component.health)
game.buff(entity_1230, 2000)
game.sub_health(entity_1230, 0)
game.add_defense(entity_1230, 13)
game.set_regen(entity_1230, 1)
game.set_alive(entity_1230, true)
game.add_component(entity_1230, game.enum.component.graphics)
game.set_mesh(entity_1230, 'cube.mesh')
game.set_material(entity_1230, 'colour/brown')
game.set_manual_scaling(entity_1230, true)
game.init_graphics_component(entity_1230)
game.set_visible(entity_1230, true)
game.set_scale(entity_1230, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1230, game.enum.component.structure)
entity_1230_residences = { entity_25 }
game.add_residences(entity_1230, 'entity_1230_residences')

entity_1231 = game.create_entity()
game.add_component(entity_1231, game.enum.component.physics)
game.set_position(entity_1231, 1100.000000, 50.000000, 0.000000)
game.set_solid(entity_1231, true)
game.set_half_height(entity_1231, 50.000000)
game.add_component(entity_1231, game.enum.component.health)
game.buff(entity_1231, 2000)
game.sub_health(entity_1231, 0)
game.add_defense(entity_1231, 13)
game.set_regen(entity_1231, 1)
game.set_alive(entity_1231, true)
game.add_component(entity_1231, game.enum.component.graphics)
game.set_mesh(entity_1231, 'cube.mesh')
game.set_material(entity_1231, 'colour/brown')
game.set_manual_scaling(entity_1231, true)
game.init_graphics_component(entity_1231)
game.set_visible(entity_1231, true)
game.set_scale(entity_1231, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1231, game.enum.component.structure)
entity_1231_residences = { entity_11 }
game.add_residences(entity_1231, 'entity_1231_residences')

entity_1232 = game.create_entity()
game.add_component(entity_1232, game.enum.component.physics)
game.set_position(entity_1232, 1100.000000, 50.000000, 100.000000)
game.set_solid(entity_1232, true)
game.set_half_height(entity_1232, 50.000000)
game.add_component(entity_1232, game.enum.component.health)
game.buff(entity_1232, 2000)
game.sub_health(entity_1232, 0)
game.add_defense(entity_1232, 13)
game.set_regen(entity_1232, 1)
game.set_alive(entity_1232, true)
game.add_component(entity_1232, game.enum.component.graphics)
game.set_mesh(entity_1232, 'cube.mesh')
game.set_material(entity_1232, 'colour/brown')
game.set_manual_scaling(entity_1232, true)
game.init_graphics_component(entity_1232)
game.set_visible(entity_1232, true)
game.set_scale(entity_1232, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1232, game.enum.component.structure)
entity_1232_residences = { entity_27 }
game.add_residences(entity_1232, 'entity_1232_residences')

entity_1233 = game.create_entity()
game.add_component(entity_1233, game.enum.component.physics)
game.set_position(entity_1233, 1100.000000, 50.000000, 200.000000)
game.set_solid(entity_1233, true)
game.set_half_height(entity_1233, 50.000000)
game.add_component(entity_1233, game.enum.component.health)
game.buff(entity_1233, 2000)
game.sub_health(entity_1233, 0)
game.add_defense(entity_1233, 13)
game.set_regen(entity_1233, 1)
game.set_alive(entity_1233, true)
game.add_component(entity_1233, game.enum.component.graphics)
game.set_mesh(entity_1233, 'cube.mesh')
game.set_material(entity_1233, 'colour/brown')
game.set_manual_scaling(entity_1233, true)
game.init_graphics_component(entity_1233)
game.set_visible(entity_1233, true)
game.set_scale(entity_1233, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1233, game.enum.component.structure)
entity_1233_residences = { entity_43 }
game.add_residences(entity_1233, 'entity_1233_residences')

entity_1234 = game.create_entity()
game.add_component(entity_1234, game.enum.component.physics)
game.set_position(entity_1234, 1200.000000, 50.000000, 400.000000)
game.set_solid(entity_1234, true)
game.set_half_height(entity_1234, 50.000000)
game.add_component(entity_1234, game.enum.component.health)
game.buff(entity_1234, 2000)
game.sub_health(entity_1234, 0)
game.add_defense(entity_1234, 13)
game.set_regen(entity_1234, 1)
game.set_alive(entity_1234, true)
game.add_component(entity_1234, game.enum.component.graphics)
game.set_mesh(entity_1234, 'cube.mesh')
game.set_material(entity_1234, 'colour/brown')
game.set_manual_scaling(entity_1234, true)
game.init_graphics_component(entity_1234)
game.set_visible(entity_1234, true)
game.set_scale(entity_1234, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1234, game.enum.component.structure)
entity_1234_residences = { entity_76 }
game.add_residences(entity_1234, 'entity_1234_residences')

entity_1235 = game.create_entity()
game.add_component(entity_1235, game.enum.component.physics)
game.set_position(entity_1235, 1400.000000, 50.000000, 400.000000)
game.set_solid(entity_1235, true)
game.set_half_height(entity_1235, 50.000000)
game.add_component(entity_1235, game.enum.component.health)
game.buff(entity_1235, 2000)
game.sub_health(entity_1235, 0)
game.add_defense(entity_1235, 13)
game.set_regen(entity_1235, 1)
game.set_alive(entity_1235, true)
game.add_component(entity_1235, game.enum.component.graphics)
game.set_mesh(entity_1235, 'cube.mesh')
game.set_material(entity_1235, 'colour/brown')
game.set_manual_scaling(entity_1235, true)
game.init_graphics_component(entity_1235)
game.set_visible(entity_1235, true)
game.set_scale(entity_1235, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1235, game.enum.component.structure)
entity_1235_residences = { entity_78 }
game.add_residences(entity_1235, 'entity_1235_residences')

entity_1236 = game.create_entity()
game.add_component(entity_1236, game.enum.component.physics)
game.set_position(entity_1236, 1500.000000, 50.000000, 400.000000)
game.set_solid(entity_1236, true)
game.set_half_height(entity_1236, 50.000000)
game.add_component(entity_1236, game.enum.component.health)
game.buff(entity_1236, 2000)
game.sub_health(entity_1236, 0)
game.add_defense(entity_1236, 13)
game.set_regen(entity_1236, 1)
game.set_alive(entity_1236, true)
game.add_component(entity_1236, game.enum.component.graphics)
game.set_mesh(entity_1236, 'cube.mesh')
game.set_material(entity_1236, 'colour/brown')
game.set_manual_scaling(entity_1236, true)
game.init_graphics_component(entity_1236)
game.set_visible(entity_1236, true)
game.set_scale(entity_1236, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1236, game.enum.component.structure)
entity_1236_residences = { entity_79 }
game.add_residences(entity_1236, 'entity_1236_residences')

entity_1237 = game.create_entity()
game.add_component(entity_1237, game.enum.component.physics)
game.set_position(entity_1237, 1200.000000, 50.000000, 600.000000)
game.set_solid(entity_1237, true)
game.set_half_height(entity_1237, 50.000000)
game.add_component(entity_1237, game.enum.component.health)
game.buff(entity_1237, 2000)
game.sub_health(entity_1237, 0)
game.add_defense(entity_1237, 13)
game.set_regen(entity_1237, 1)
game.set_alive(entity_1237, true)
game.add_component(entity_1237, game.enum.component.graphics)
game.set_mesh(entity_1237, 'cube.mesh')
game.set_material(entity_1237, 'colour/brown')
game.set_manual_scaling(entity_1237, true)
game.init_graphics_component(entity_1237)
game.set_visible(entity_1237, true)
game.set_scale(entity_1237, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1237, game.enum.component.structure)
entity_1237_residences = { entity_108 }
game.add_residences(entity_1237, 'entity_1237_residences')

entity_1238 = game.create_entity()
game.add_component(entity_1238, game.enum.component.physics)
game.set_position(entity_1238, 1300.000000, 50.000000, 600.000000)
game.set_solid(entity_1238, true)
game.set_half_height(entity_1238, 50.000000)
game.add_component(entity_1238, game.enum.component.health)
game.buff(entity_1238, 2000)
game.sub_health(entity_1238, 0)
game.add_defense(entity_1238, 13)
game.set_regen(entity_1238, 1)
game.set_alive(entity_1238, true)
game.add_component(entity_1238, game.enum.component.graphics)
game.set_mesh(entity_1238, 'cube.mesh')
game.set_material(entity_1238, 'colour/brown')
game.set_manual_scaling(entity_1238, true)
game.init_graphics_component(entity_1238)
game.set_visible(entity_1238, true)
game.set_scale(entity_1238, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1238, game.enum.component.structure)
entity_1238_residences = { entity_109 }
game.add_residences(entity_1238, 'entity_1238_residences')

entity_1239 = game.create_entity()
game.add_component(entity_1239, game.enum.component.physics)
game.set_position(entity_1239, 1500.000000, 50.000000, 600.000000)
game.set_solid(entity_1239, true)
game.set_half_height(entity_1239, 50.000000)
game.add_component(entity_1239, game.enum.component.health)
game.buff(entity_1239, 2000)
game.sub_health(entity_1239, 0)
game.add_defense(entity_1239, 13)
game.set_regen(entity_1239, 1)
game.set_alive(entity_1239, true)
game.add_component(entity_1239, game.enum.component.graphics)
game.set_mesh(entity_1239, 'cube.mesh')
game.set_material(entity_1239, 'colour/brown')
game.set_manual_scaling(entity_1239, true)
game.init_graphics_component(entity_1239)
game.set_visible(entity_1239, true)
game.set_scale(entity_1239, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1239, game.enum.component.structure)
entity_1239_residences = { entity_111 }
game.add_residences(entity_1239, 'entity_1239_residences')

entity_1240 = game.create_entity()
game.add_component(entity_1240, game.enum.component.physics)
game.set_position(entity_1240, 1500.000000, 50.000000, 800.000000)
game.set_solid(entity_1240, true)
game.set_half_height(entity_1240, 50.000000)
game.add_component(entity_1240, game.enum.component.health)
game.buff(entity_1240, 2000)
game.sub_health(entity_1240, 0)
game.add_defense(entity_1240, 13)
game.set_regen(entity_1240, 1)
game.set_alive(entity_1240, true)
game.add_component(entity_1240, game.enum.component.graphics)
game.set_mesh(entity_1240, 'cube.mesh')
game.set_material(entity_1240, 'colour/brown')
game.set_manual_scaling(entity_1240, true)
game.init_graphics_component(entity_1240)
game.set_visible(entity_1240, true)
game.set_scale(entity_1240, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1240, game.enum.component.structure)
entity_1240_residences = { entity_143 }
game.add_residences(entity_1240, 'entity_1240_residences')

entity_1241 = game.create_entity()
game.add_component(entity_1241, game.enum.component.physics)
game.set_position(entity_1241, 1400.000000, 50.000000, 800.000000)
game.set_solid(entity_1241, true)
game.set_half_height(entity_1241, 50.000000)
game.add_component(entity_1241, game.enum.component.health)
game.buff(entity_1241, 2000)
game.sub_health(entity_1241, 0)
game.add_defense(entity_1241, 13)
game.set_regen(entity_1241, 1)
game.set_alive(entity_1241, true)
game.add_component(entity_1241, game.enum.component.graphics)
game.set_mesh(entity_1241, 'cube.mesh')
game.set_material(entity_1241, 'colour/brown')
game.set_manual_scaling(entity_1241, true)
game.init_graphics_component(entity_1241)
game.set_visible(entity_1241, true)
game.set_scale(entity_1241, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1241, game.enum.component.structure)
entity_1241_residences = { entity_142 }
game.add_residences(entity_1241, 'entity_1241_residences')

entity_1242 = game.create_entity()
game.add_component(entity_1242, game.enum.component.physics)
game.set_position(entity_1242, 1200.000000, 50.000000, 800.000000)
game.set_solid(entity_1242, true)
game.set_half_height(entity_1242, 50.000000)
game.add_component(entity_1242, game.enum.component.health)
game.buff(entity_1242, 2000)
game.sub_health(entity_1242, 0)
game.add_defense(entity_1242, 13)
game.set_regen(entity_1242, 1)
game.set_alive(entity_1242, true)
game.add_component(entity_1242, game.enum.component.graphics)
game.set_mesh(entity_1242, 'cube.mesh')
game.set_material(entity_1242, 'colour/brown')
game.set_manual_scaling(entity_1242, true)
game.init_graphics_component(entity_1242)
game.set_visible(entity_1242, true)
game.set_scale(entity_1242, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1242, game.enum.component.structure)
entity_1242_residences = { entity_140 }
game.add_residences(entity_1242, 'entity_1242_residences')

entity_1243 = game.create_entity()
game.add_component(entity_1243, game.enum.component.physics)
game.set_position(entity_1243, 1200.000000, 50.000000, 1000.000000)
game.set_solid(entity_1243, true)
game.set_half_height(entity_1243, 50.000000)
game.add_component(entity_1243, game.enum.component.health)
game.buff(entity_1243, 2000)
game.sub_health(entity_1243, 0)
game.add_defense(entity_1243, 13)
game.set_regen(entity_1243, 1)
game.set_alive(entity_1243, true)
game.add_component(entity_1243, game.enum.component.graphics)
game.set_mesh(entity_1243, 'cube.mesh')
game.set_material(entity_1243, 'colour/brown')
game.set_manual_scaling(entity_1243, true)
game.init_graphics_component(entity_1243)
game.set_visible(entity_1243, true)
game.set_scale(entity_1243, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1243, game.enum.component.structure)
entity_1243_residences = { entity_172 }
game.add_residences(entity_1243, 'entity_1243_residences')

entity_1244 = game.create_entity()
game.add_component(entity_1244, game.enum.component.physics)
game.set_position(entity_1244, 1300.000000, 50.000000, 1000.000000)
game.set_solid(entity_1244, true)
game.set_half_height(entity_1244, 50.000000)
game.add_component(entity_1244, game.enum.component.health)
game.buff(entity_1244, 2000)
game.sub_health(entity_1244, 0)
game.add_defense(entity_1244, 13)
game.set_regen(entity_1244, 1)
game.set_alive(entity_1244, true)
game.add_component(entity_1244, game.enum.component.graphics)
game.set_mesh(entity_1244, 'cube.mesh')
game.set_material(entity_1244, 'colour/brown')
game.set_manual_scaling(entity_1244, true)
game.init_graphics_component(entity_1244)
game.set_visible(entity_1244, true)
game.set_scale(entity_1244, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1244, game.enum.component.structure)
entity_1244_residences = { entity_173 }
game.add_residences(entity_1244, 'entity_1244_residences')

entity_1245 = game.create_entity()
game.add_component(entity_1245, game.enum.component.physics)
game.set_position(entity_1245, 1500.000000, 50.000000, 1000.000000)
game.set_solid(entity_1245, true)
game.set_half_height(entity_1245, 50.000000)
game.add_component(entity_1245, game.enum.component.health)
game.buff(entity_1245, 2000)
game.sub_health(entity_1245, 0)
game.add_defense(entity_1245, 13)
game.set_regen(entity_1245, 1)
game.set_alive(entity_1245, true)
game.add_component(entity_1245, game.enum.component.graphics)
game.set_mesh(entity_1245, 'cube.mesh')
game.set_material(entity_1245, 'colour/brown')
game.set_manual_scaling(entity_1245, true)
game.init_graphics_component(entity_1245)
game.set_visible(entity_1245, true)
game.set_scale(entity_1245, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1245, game.enum.component.structure)
entity_1245_residences = { entity_175 }
game.add_residences(entity_1245, 'entity_1245_residences')

entity_1246 = game.create_entity()
game.add_component(entity_1246, game.enum.component.physics)
game.set_position(entity_1246, 1300.000000, 50.000000, 1100.000000)
game.set_solid(entity_1246, true)
game.set_half_height(entity_1246, 50.000000)
game.add_component(entity_1246, game.enum.component.health)
game.buff(entity_1246, 2000)
game.sub_health(entity_1246, 0)
game.add_defense(entity_1246, 13)
game.set_regen(entity_1246, 1)
game.set_alive(entity_1246, true)
game.add_component(entity_1246, game.enum.component.graphics)
game.set_mesh(entity_1246, 'cube.mesh')
game.set_material(entity_1246, 'colour/brown')
game.set_manual_scaling(entity_1246, true)
game.init_graphics_component(entity_1246)
game.set_visible(entity_1246, true)
game.set_scale(entity_1246, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1246, game.enum.component.structure)
entity_1246_residences = { entity_189 }
game.add_residences(entity_1246, 'entity_1246_residences')

entity_1247 = game.create_entity()
game.add_component(entity_1247, game.enum.component.physics)
game.set_position(entity_1247, 1300.000000, 50.000000, 1200.000000)
game.set_solid(entity_1247, true)
game.set_half_height(entity_1247, 50.000000)
game.add_component(entity_1247, game.enum.component.health)
game.buff(entity_1247, 2000)
game.sub_health(entity_1247, 0)
game.add_defense(entity_1247, 13)
game.set_regen(entity_1247, 1)
game.set_alive(entity_1247, true)
game.add_component(entity_1247, game.enum.component.graphics)
game.set_mesh(entity_1247, 'cube.mesh')
game.set_material(entity_1247, 'colour/brown')
game.set_manual_scaling(entity_1247, true)
game.init_graphics_component(entity_1247)
game.set_visible(entity_1247, true)
game.set_scale(entity_1247, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1247, game.enum.component.structure)
entity_1247_residences = { entity_205 }
game.add_residences(entity_1247, 'entity_1247_residences')

entity_1248 = game.create_entity()
game.add_component(entity_1248, game.enum.component.physics)
game.set_position(entity_1248, 1300.000000, 50.000000, 1300.000000)
game.set_solid(entity_1248, true)
game.set_half_height(entity_1248, 50.000000)
game.add_component(entity_1248, game.enum.component.health)
game.buff(entity_1248, 2000)
game.sub_health(entity_1248, 0)
game.add_defense(entity_1248, 13)
game.set_regen(entity_1248, 1)
game.set_alive(entity_1248, true)
game.add_component(entity_1248, game.enum.component.graphics)
game.set_mesh(entity_1248, 'cube.mesh')
game.set_material(entity_1248, 'colour/brown')
game.set_manual_scaling(entity_1248, true)
game.init_graphics_component(entity_1248)
game.set_visible(entity_1248, true)
game.set_scale(entity_1248, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1248, game.enum.component.structure)
entity_1248_residences = { entity_221 }
game.add_residences(entity_1248, 'entity_1248_residences')

entity_1249 = game.create_entity()
game.add_component(entity_1249, game.enum.component.physics)
game.set_position(entity_1249, 1100.000000, 50.000000, 1500.000000)
game.set_solid(entity_1249, true)
game.set_half_height(entity_1249, 50.000000)
game.add_component(entity_1249, game.enum.component.health)
game.buff(entity_1249, 2000)
game.sub_health(entity_1249, 0)
game.add_defense(entity_1249, 13)
game.set_regen(entity_1249, 1)
game.set_alive(entity_1249, true)
game.add_component(entity_1249, game.enum.component.graphics)
game.set_mesh(entity_1249, 'cube.mesh')
game.set_material(entity_1249, 'colour/brown')
game.set_manual_scaling(entity_1249, true)
game.init_graphics_component(entity_1249)
game.set_visible(entity_1249, true)
game.set_scale(entity_1249, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1249, game.enum.component.structure)
entity_1249_residences = { entity_251 }
game.add_residences(entity_1249, 'entity_1249_residences')

entity_1250 = game.create_entity()
game.add_component(entity_1250, game.enum.component.physics)
game.set_position(entity_1250, 1100.000000, 50.000000, 1400.000000)
game.set_solid(entity_1250, true)
game.set_half_height(entity_1250, 50.000000)
game.add_component(entity_1250, game.enum.component.health)
game.buff(entity_1250, 2000)
game.sub_health(entity_1250, 0)
game.add_defense(entity_1250, 13)
game.set_regen(entity_1250, 1)
game.set_alive(entity_1250, true)
game.add_component(entity_1250, game.enum.component.graphics)
game.set_mesh(entity_1250, 'cube.mesh')
game.set_material(entity_1250, 'colour/brown')
game.set_manual_scaling(entity_1250, true)
game.init_graphics_component(entity_1250)
game.set_visible(entity_1250, true)
game.set_scale(entity_1250, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1250, game.enum.component.structure)
entity_1250_residences = { entity_235 }
game.add_residences(entity_1250, 'entity_1250_residences')

entity_1251 = game.create_entity()
game.add_component(entity_1251, game.enum.component.physics)
game.set_position(entity_1251, 1100.000000, 50.000000, 1300.000000)
game.set_solid(entity_1251, true)
game.set_half_height(entity_1251, 50.000000)
game.add_component(entity_1251, game.enum.component.health)
game.buff(entity_1251, 2000)
game.sub_health(entity_1251, 0)
game.add_defense(entity_1251, 13)
game.set_regen(entity_1251, 1)
game.set_alive(entity_1251, true)
game.add_component(entity_1251, game.enum.component.graphics)
game.set_mesh(entity_1251, 'cube.mesh')
game.set_material(entity_1251, 'colour/brown')
game.set_manual_scaling(entity_1251, true)
game.init_graphics_component(entity_1251)
game.set_visible(entity_1251, true)
game.set_scale(entity_1251, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1251, game.enum.component.structure)
entity_1251_residences = { entity_219 }
game.add_residences(entity_1251, 'entity_1251_residences')

entity_1252 = game.create_entity()
game.add_component(entity_1252, game.enum.component.physics)
game.set_position(entity_1252, 1100.000000, 50.000000, 1200.000000)
game.set_solid(entity_1252, true)
game.set_half_height(entity_1252, 50.000000)
game.add_component(entity_1252, game.enum.component.health)
game.buff(entity_1252, 2000)
game.sub_health(entity_1252, 0)
game.add_defense(entity_1252, 13)
game.set_regen(entity_1252, 1)
game.set_alive(entity_1252, true)
game.add_component(entity_1252, game.enum.component.graphics)
game.set_mesh(entity_1252, 'cube.mesh')
game.set_material(entity_1252, 'colour/brown')
game.set_manual_scaling(entity_1252, true)
game.init_graphics_component(entity_1252)
game.set_visible(entity_1252, true)
game.set_scale(entity_1252, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1252, game.enum.component.structure)
entity_1252_residences = { entity_203 }
game.add_residences(entity_1252, 'entity_1252_residences')

entity_1253 = game.create_entity()
game.add_component(entity_1253, game.enum.component.physics)
game.set_position(entity_1253, 700.000000, 27.008251, 1200.000000)
game.set_solid(entity_1253, false)
game.set_half_height(entity_1253, 27.008251)
game.add_component(entity_1253, game.enum.component.health)
game.buff(entity_1253, 1000)
game.sub_health(entity_1253, 0)
game.add_defense(entity_1253, 8)
game.set_regen(entity_1253, 1)
game.set_alive(entity_1253, true)
game.add_component(entity_1253, game.enum.component.ai)
game.set_blueprint(entity_1253, 'ogre')
game.set_state(entity_1253, 1)
game.set_faction(entity_1253, 0)
game.add_component(entity_1253, game.enum.component.graphics)
game.set_mesh(entity_1253, 'ogrehead.mesh')
game.set_material(entity_1253, 'NO_MAT')
game.set_manual_scaling(entity_1253, false)
game.init_graphics_component(entity_1253)
game.set_visible(entity_1253, true)
game.add_component(entity_1253, game.enum.component.movement)
game.set_speed(entity_1253, 0.500000)
game.add_component(entity_1253, game.enum.component.pathfinding)
game.set_pathfinding_blueprint(entity_1253, 'ogre')
game.add_component(entity_1253, game.enum.component.task_handler)
game.add_possible_task(entity_1253, 1)
game.add_possible_task(entity_1253, 2)

entity_1254 = game.create_entity()
game.add_component(entity_1254, game.enum.component.physics)
game.set_position(entity_1254, 700.000000, 50.000000, 400.000000)
game.set_solid(entity_1254, true)
game.set_half_height(entity_1254, 50.000000)
game.add_component(entity_1254, game.enum.component.health)
game.buff(entity_1254, 2000)
game.sub_health(entity_1254, 0)
game.add_defense(entity_1254, 13)
game.set_regen(entity_1254, 1)
game.set_alive(entity_1254, true)
game.add_component(entity_1254, game.enum.component.graphics)
game.set_mesh(entity_1254, 'cube.mesh')
game.set_material(entity_1254, 'colour/brown')
game.set_manual_scaling(entity_1254, true)
game.init_graphics_component(entity_1254)
game.set_visible(entity_1254, true)
game.set_scale(entity_1254, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1254, game.enum.component.structure)
entity_1254_residences = { entity_71 }
game.add_residences(entity_1254, 'entity_1254_residences')

entity_1255 = game.create_entity()
game.add_component(entity_1255, game.enum.component.physics)
game.set_position(entity_1255, 600.000000, 50.000000, 400.000000)
game.set_solid(entity_1255, true)
game.set_half_height(entity_1255, 50.000000)
game.add_component(entity_1255, game.enum.component.health)
game.buff(entity_1255, 2000)
game.sub_health(entity_1255, 0)
game.add_defense(entity_1255, 13)
game.set_regen(entity_1255, 1)
game.set_alive(entity_1255, true)
game.add_component(entity_1255, game.enum.component.graphics)
game.set_mesh(entity_1255, 'cube.mesh')
game.set_material(entity_1255, 'colour/brown')
game.set_manual_scaling(entity_1255, true)
game.init_graphics_component(entity_1255)
game.set_visible(entity_1255, true)
game.set_scale(entity_1255, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1255, game.enum.component.structure)
entity_1255_residences = { entity_70 }
game.add_residences(entity_1255, 'entity_1255_residences')

entity_1256 = game.create_entity()
game.add_component(entity_1256, game.enum.component.physics)
game.set_position(entity_1256, 500.000000, 50.000000, 400.000000)
game.set_solid(entity_1256, true)
game.set_half_height(entity_1256, 50.000000)
game.add_component(entity_1256, game.enum.component.health)
game.buff(entity_1256, 2000)
game.sub_health(entity_1256, 0)
game.add_defense(entity_1256, 13)
game.set_regen(entity_1256, 1)
game.set_alive(entity_1256, true)
game.add_component(entity_1256, game.enum.component.graphics)
game.set_mesh(entity_1256, 'cube.mesh')
game.set_material(entity_1256, 'colour/brown')
game.set_manual_scaling(entity_1256, true)
game.init_graphics_component(entity_1256)
game.set_visible(entity_1256, true)
game.set_scale(entity_1256, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1256, game.enum.component.structure)
entity_1256_residences = { entity_69 }
game.add_residences(entity_1256, 'entity_1256_residences')

entity_1257 = game.create_entity()
game.add_component(entity_1257, game.enum.component.physics)
game.set_position(entity_1257, 400.000000, 50.000000, 400.000000)
game.set_solid(entity_1257, true)
game.set_half_height(entity_1257, 50.000000)
game.add_component(entity_1257, game.enum.component.health)
game.buff(entity_1257, 2000)
game.sub_health(entity_1257, 0)
game.add_defense(entity_1257, 13)
game.set_regen(entity_1257, 1)
game.set_alive(entity_1257, true)
game.add_component(entity_1257, game.enum.component.graphics)
game.set_mesh(entity_1257, 'cube.mesh')
game.set_material(entity_1257, 'colour/brown')
game.set_manual_scaling(entity_1257, true)
game.init_graphics_component(entity_1257)
game.set_visible(entity_1257, true)
game.set_scale(entity_1257, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1257, game.enum.component.structure)
entity_1257_residences = { entity_68 }
game.add_residences(entity_1257, 'entity_1257_residences')

entity_1258 = game.create_entity()
game.add_component(entity_1258, game.enum.component.physics)
game.set_position(entity_1258, 200.000000, 50.000000, 400.000000)
game.set_solid(entity_1258, true)
game.set_half_height(entity_1258, 50.000000)
game.add_component(entity_1258, game.enum.component.health)
game.buff(entity_1258, 2000)
game.sub_health(entity_1258, 0)
game.add_defense(entity_1258, 13)
game.set_regen(entity_1258, 1)
game.set_alive(entity_1258, true)
game.add_component(entity_1258, game.enum.component.graphics)
game.set_mesh(entity_1258, 'cube.mesh')
game.set_material(entity_1258, 'colour/brown')
game.set_manual_scaling(entity_1258, true)
game.init_graphics_component(entity_1258)
game.set_visible(entity_1258, true)
game.set_scale(entity_1258, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1258, game.enum.component.structure)
entity_1258_residences = { entity_66 }
game.add_residences(entity_1258, 'entity_1258_residences')

entity_1259 = game.create_entity()
game.add_component(entity_1259, game.enum.component.physics)
game.set_position(entity_1259, 100.000000, 50.000000, 400.000000)
game.set_solid(entity_1259, true)
game.set_half_height(entity_1259, 50.000000)
game.add_component(entity_1259, game.enum.component.health)
game.buff(entity_1259, 2000)
game.sub_health(entity_1259, 0)
game.add_defense(entity_1259, 13)
game.set_regen(entity_1259, 1)
game.set_alive(entity_1259, true)
game.add_component(entity_1259, game.enum.component.graphics)
game.set_mesh(entity_1259, 'cube.mesh')
game.set_material(entity_1259, 'colour/brown')
game.set_manual_scaling(entity_1259, true)
game.init_graphics_component(entity_1259)
game.set_visible(entity_1259, true)
game.set_scale(entity_1259, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1259, game.enum.component.structure)
entity_1259_residences = { entity_65 }
game.add_residences(entity_1259, 'entity_1259_residences')

entity_1260 = game.create_entity()
game.add_component(entity_1260, game.enum.component.physics)
game.set_position(entity_1260, 0.000000, 50.000000, 400.000000)
game.set_solid(entity_1260, true)
game.set_half_height(entity_1260, 50.000000)
game.add_component(entity_1260, game.enum.component.health)
game.buff(entity_1260, 2000)
game.sub_health(entity_1260, 0)
game.add_defense(entity_1260, 13)
game.set_regen(entity_1260, 1)
game.set_alive(entity_1260, true)
game.add_component(entity_1260, game.enum.component.graphics)
game.set_mesh(entity_1260, 'cube.mesh')
game.set_material(entity_1260, 'colour/brown')
game.set_manual_scaling(entity_1260, true)
game.init_graphics_component(entity_1260)
game.set_visible(entity_1260, true)
game.set_scale(entity_1260, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1260, game.enum.component.structure)
entity_1260_residences = { entity_64 }
game.add_residences(entity_1260, 'entity_1260_residences')

entity_1261 = game.create_entity()
game.add_component(entity_1261, game.enum.component.physics)
game.set_position(entity_1261, 0.000000, 50.000000, 200.000000)
game.set_solid(entity_1261, true)
game.set_half_height(entity_1261, 50.000000)
game.add_component(entity_1261, game.enum.component.health)
game.buff(entity_1261, 2000)
game.sub_health(entity_1261, 0)
game.add_defense(entity_1261, 13)
game.set_regen(entity_1261, 1)
game.set_alive(entity_1261, true)
game.add_component(entity_1261, game.enum.component.graphics)
game.set_mesh(entity_1261, 'cube.mesh')
game.set_material(entity_1261, 'colour/brown')
game.set_manual_scaling(entity_1261, true)
game.init_graphics_component(entity_1261)
game.set_visible(entity_1261, true)
game.set_scale(entity_1261, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1261, game.enum.component.structure)
entity_1261_residences = { entity_32 }
game.add_residences(entity_1261, 'entity_1261_residences')

entity_1262 = game.create_entity()
game.add_component(entity_1262, game.enum.component.physics)
game.set_position(entity_1262, 100.000000, 50.000000, 200.000000)
game.set_solid(entity_1262, true)
game.set_half_height(entity_1262, 50.000000)
game.add_component(entity_1262, game.enum.component.health)
game.buff(entity_1262, 2000)
game.sub_health(entity_1262, 0)
game.add_defense(entity_1262, 13)
game.set_regen(entity_1262, 1)
game.set_alive(entity_1262, true)
game.add_component(entity_1262, game.enum.component.graphics)
game.set_mesh(entity_1262, 'cube.mesh')
game.set_material(entity_1262, 'colour/brown')
game.set_manual_scaling(entity_1262, true)
game.init_graphics_component(entity_1262)
game.set_visible(entity_1262, true)
game.set_scale(entity_1262, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1262, game.enum.component.structure)
entity_1262_residences = { entity_33 }
game.add_residences(entity_1262, 'entity_1262_residences')

entity_1263 = game.create_entity()
game.add_component(entity_1263, game.enum.component.physics)
game.set_position(entity_1263, 300.000000, 50.000000, 200.000000)
game.set_solid(entity_1263, true)
game.set_half_height(entity_1263, 50.000000)
game.add_component(entity_1263, game.enum.component.health)
game.buff(entity_1263, 2000)
game.sub_health(entity_1263, 0)
game.add_defense(entity_1263, 13)
game.set_regen(entity_1263, 1)
game.set_alive(entity_1263, true)
game.add_component(entity_1263, game.enum.component.graphics)
game.set_mesh(entity_1263, 'cube.mesh')
game.set_material(entity_1263, 'colour/brown')
game.set_manual_scaling(entity_1263, true)
game.init_graphics_component(entity_1263)
game.set_visible(entity_1263, true)
game.set_scale(entity_1263, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1263, game.enum.component.structure)
entity_1263_residences = { entity_35 }
game.add_residences(entity_1263, 'entity_1263_residences')

entity_1264 = game.create_entity()
game.add_component(entity_1264, game.enum.component.physics)
game.set_position(entity_1264, 400.000000, 50.000000, 200.000000)
game.set_solid(entity_1264, true)
game.set_half_height(entity_1264, 50.000000)
game.add_component(entity_1264, game.enum.component.health)
game.buff(entity_1264, 2000)
game.sub_health(entity_1264, 0)
game.add_defense(entity_1264, 13)
game.set_regen(entity_1264, 1)
game.set_alive(entity_1264, true)
game.add_component(entity_1264, game.enum.component.graphics)
game.set_mesh(entity_1264, 'cube.mesh')
game.set_material(entity_1264, 'colour/brown')
game.set_manual_scaling(entity_1264, true)
game.init_graphics_component(entity_1264)
game.set_visible(entity_1264, true)
game.set_scale(entity_1264, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1264, game.enum.component.structure)
entity_1264_residences = { entity_36 }
game.add_residences(entity_1264, 'entity_1264_residences')

entity_1265 = game.create_entity()
game.add_component(entity_1265, game.enum.component.physics)
game.set_position(entity_1265, 600.000000, 50.000000, 200.000000)
game.set_solid(entity_1265, true)
game.set_half_height(entity_1265, 50.000000)
game.add_component(entity_1265, game.enum.component.health)
game.buff(entity_1265, 2000)
game.sub_health(entity_1265, 0)
game.add_defense(entity_1265, 13)
game.set_regen(entity_1265, 1)
game.set_alive(entity_1265, true)
game.add_component(entity_1265, game.enum.component.graphics)
game.set_mesh(entity_1265, 'cube.mesh')
game.set_material(entity_1265, 'colour/brown')
game.set_manual_scaling(entity_1265, true)
game.init_graphics_component(entity_1265)
game.set_visible(entity_1265, true)
game.set_scale(entity_1265, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1265, game.enum.component.structure)
entity_1265_residences = { entity_38 }
game.add_residences(entity_1265, 'entity_1265_residences')

entity_1266 = game.create_entity()
game.add_component(entity_1266, game.enum.component.physics)
game.set_position(entity_1266, 700.000000, 50.000000, 200.000000)
game.set_solid(entity_1266, true)
game.set_half_height(entity_1266, 50.000000)
game.add_component(entity_1266, game.enum.component.health)
game.buff(entity_1266, 2000)
game.sub_health(entity_1266, 0)
game.add_defense(entity_1266, 13)
game.set_regen(entity_1266, 1)
game.set_alive(entity_1266, true)
game.add_component(entity_1266, game.enum.component.graphics)
game.set_mesh(entity_1266, 'cube.mesh')
game.set_material(entity_1266, 'colour/brown')
game.set_manual_scaling(entity_1266, true)
game.init_graphics_component(entity_1266)
game.set_visible(entity_1266, true)
game.set_scale(entity_1266, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1266, game.enum.component.structure)
entity_1266_residences = { entity_39 }
game.add_residences(entity_1266, 'entity_1266_residences')

entity_1267 = game.create_entity()
game.add_component(entity_1267, game.enum.component.physics)
game.set_position(entity_1267, 600.000000, 50.000000, 100.000000)
game.set_solid(entity_1267, true)
game.set_half_height(entity_1267, 50.000000)
game.add_component(entity_1267, game.enum.component.health)
game.buff(entity_1267, 2000)
game.sub_health(entity_1267, 0)
game.add_defense(entity_1267, 13)
game.set_regen(entity_1267, 1)
game.set_alive(entity_1267, true)
game.add_component(entity_1267, game.enum.component.graphics)
game.set_mesh(entity_1267, 'cube.mesh')
game.set_material(entity_1267, 'colour/brown')
game.set_manual_scaling(entity_1267, true)
game.init_graphics_component(entity_1267)
game.set_visible(entity_1267, true)
game.set_scale(entity_1267, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1267, game.enum.component.structure)
entity_1267_residences = { entity_22 }
game.add_residences(entity_1267, 'entity_1267_residences')

entity_1268 = game.create_entity()
game.add_component(entity_1268, game.enum.component.physics)
game.set_position(entity_1268, 600.000000, 50.000000, 800.000000)
game.set_solid(entity_1268, true)
game.set_half_height(entity_1268, 50.000000)
game.add_component(entity_1268, game.enum.component.health)
game.buff(entity_1268, 2000)
game.sub_health(entity_1268, 0)
game.add_defense(entity_1268, 13)
game.set_regen(entity_1268, 1)
game.set_alive(entity_1268, true)
game.add_component(entity_1268, game.enum.component.graphics)
game.set_mesh(entity_1268, 'cube.mesh')
game.set_material(entity_1268, 'colour/brown')
game.set_manual_scaling(entity_1268, true)
game.init_graphics_component(entity_1268)
game.set_visible(entity_1268, true)
game.set_scale(entity_1268, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1268, game.enum.component.structure)
entity_1268_residences = { entity_134 }
game.add_residences(entity_1268, 'entity_1268_residences')

entity_1269 = game.create_entity()
game.add_component(entity_1269, game.enum.component.physics)
game.set_position(entity_1269, 600.000000, 50.000000, 700.000000)
game.set_solid(entity_1269, true)
game.set_half_height(entity_1269, 50.000000)
game.add_component(entity_1269, game.enum.component.health)
game.buff(entity_1269, 2000)
game.sub_health(entity_1269, 0)
game.add_defense(entity_1269, 13)
game.set_regen(entity_1269, 1)
game.set_alive(entity_1269, true)
game.add_component(entity_1269, game.enum.component.graphics)
game.set_mesh(entity_1269, 'cube.mesh')
game.set_material(entity_1269, 'colour/brown')
game.set_manual_scaling(entity_1269, true)
game.init_graphics_component(entity_1269)
game.set_visible(entity_1269, true)
game.set_scale(entity_1269, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1269, game.enum.component.structure)
entity_1269_residences = { entity_118 }
game.add_residences(entity_1269, 'entity_1269_residences')

entity_1270 = game.create_entity()
game.add_component(entity_1270, game.enum.component.physics)
game.set_position(entity_1270, 400.000000, 50.000000, 900.000000)
game.set_solid(entity_1270, true)
game.set_half_height(entity_1270, 50.000000)
game.add_component(entity_1270, game.enum.component.health)
game.buff(entity_1270, 2000)
game.sub_health(entity_1270, 0)
game.add_defense(entity_1270, 13)
game.set_regen(entity_1270, 1)
game.set_alive(entity_1270, true)
game.add_component(entity_1270, game.enum.component.graphics)
game.set_mesh(entity_1270, 'cube.mesh')
game.set_material(entity_1270, 'colour/brown')
game.set_manual_scaling(entity_1270, true)
game.init_graphics_component(entity_1270)
game.set_visible(entity_1270, true)
game.set_scale(entity_1270, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1270, game.enum.component.structure)
entity_1270_residences = { entity_148 }
game.add_residences(entity_1270, 'entity_1270_residences')

entity_1271 = game.create_entity()
game.add_component(entity_1271, game.enum.component.physics)
game.set_position(entity_1271, 400.000000, 50.000000, 800.000000)
game.set_solid(entity_1271, true)
game.set_half_height(entity_1271, 50.000000)
game.add_component(entity_1271, game.enum.component.health)
game.buff(entity_1271, 2000)
game.sub_health(entity_1271, 0)
game.add_defense(entity_1271, 13)
game.set_regen(entity_1271, 1)
game.set_alive(entity_1271, true)
game.add_component(entity_1271, game.enum.component.graphics)
game.set_mesh(entity_1271, 'cube.mesh')
game.set_material(entity_1271, 'colour/brown')
game.set_manual_scaling(entity_1271, true)
game.init_graphics_component(entity_1271)
game.set_visible(entity_1271, true)
game.set_scale(entity_1271, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1271, game.enum.component.structure)
entity_1271_residences = { entity_132 }
game.add_residences(entity_1271, 'entity_1271_residences')

entity_1272 = game.create_entity()
game.add_component(entity_1272, game.enum.component.physics)
game.set_position(entity_1272, 400.000000, 50.000000, 500.000000)
game.set_solid(entity_1272, true)
game.set_half_height(entity_1272, 50.000000)
game.add_component(entity_1272, game.enum.component.health)
game.buff(entity_1272, 2000)
game.sub_health(entity_1272, 0)
game.add_defense(entity_1272, 13)
game.set_regen(entity_1272, 1)
game.set_alive(entity_1272, true)
game.add_component(entity_1272, game.enum.component.graphics)
game.set_mesh(entity_1272, 'cube.mesh')
game.set_material(entity_1272, 'colour/brown')
game.set_manual_scaling(entity_1272, true)
game.init_graphics_component(entity_1272)
game.set_visible(entity_1272, true)
game.set_scale(entity_1272, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1272, game.enum.component.structure)
entity_1272_residences = { entity_84 }
game.add_residences(entity_1272, 'entity_1272_residences')

entity_1273 = game.create_entity()
game.add_component(entity_1273, game.enum.component.physics)
game.set_position(entity_1273, 400.000000, 50.000000, 600.000000)
game.set_solid(entity_1273, true)
game.set_half_height(entity_1273, 50.000000)
game.add_component(entity_1273, game.enum.component.health)
game.buff(entity_1273, 2000)
game.sub_health(entity_1273, 0)
game.add_defense(entity_1273, 13)
game.set_regen(entity_1273, 1)
game.set_alive(entity_1273, true)
game.add_component(entity_1273, game.enum.component.graphics)
game.set_mesh(entity_1273, 'cube.mesh')
game.set_material(entity_1273, 'colour/brown')
game.set_manual_scaling(entity_1273, true)
game.init_graphics_component(entity_1273)
game.set_visible(entity_1273, true)
game.set_scale(entity_1273, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1273, game.enum.component.structure)
entity_1273_residences = { entity_100 }
game.add_residences(entity_1273, 'entity_1273_residences')

entity_1274 = game.create_entity()
game.add_component(entity_1274, game.enum.component.physics)
game.set_position(entity_1274, 200.000000, 50.000000, 800.000000)
game.set_solid(entity_1274, true)
game.set_half_height(entity_1274, 50.000000)
game.add_component(entity_1274, game.enum.component.health)
game.buff(entity_1274, 2000)
game.sub_health(entity_1274, 0)
game.add_defense(entity_1274, 13)
game.set_regen(entity_1274, 1)
game.set_alive(entity_1274, true)
game.add_component(entity_1274, game.enum.component.graphics)
game.set_mesh(entity_1274, 'cube.mesh')
game.set_material(entity_1274, 'colour/brown')
game.set_manual_scaling(entity_1274, true)
game.init_graphics_component(entity_1274)
game.set_visible(entity_1274, true)
game.set_scale(entity_1274, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1274, game.enum.component.structure)
entity_1274_residences = { entity_130 }
game.add_residences(entity_1274, 'entity_1274_residences')

entity_1275 = game.create_entity()
game.add_component(entity_1275, game.enum.component.physics)
game.set_position(entity_1275, 200.000000, 50.000000, 700.000000)
game.set_solid(entity_1275, true)
game.set_half_height(entity_1275, 50.000000)
game.add_component(entity_1275, game.enum.component.health)
game.buff(entity_1275, 2000)
game.sub_health(entity_1275, 0)
game.add_defense(entity_1275, 13)
game.set_regen(entity_1275, 1)
game.set_alive(entity_1275, true)
game.add_component(entity_1275, game.enum.component.graphics)
game.set_mesh(entity_1275, 'cube.mesh')
game.set_material(entity_1275, 'colour/brown')
game.set_manual_scaling(entity_1275, true)
game.init_graphics_component(entity_1275)
game.set_visible(entity_1275, true)
game.set_scale(entity_1275, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1275, game.enum.component.structure)
entity_1275_residences = { entity_114 }
game.add_residences(entity_1275, 'entity_1275_residences')

entity_1276 = game.create_entity()
game.add_component(entity_1276, game.enum.component.physics)
game.set_position(entity_1276, 100.000000, 50.000000, 600.000000)
game.set_solid(entity_1276, true)
game.set_half_height(entity_1276, 50.000000)
game.add_component(entity_1276, game.enum.component.health)
game.buff(entity_1276, 2000)
game.sub_health(entity_1276, 0)
game.add_defense(entity_1276, 13)
game.set_regen(entity_1276, 1)
game.set_alive(entity_1276, true)
game.add_component(entity_1276, game.enum.component.graphics)
game.set_mesh(entity_1276, 'cube.mesh')
game.set_material(entity_1276, 'colour/brown')
game.set_manual_scaling(entity_1276, true)
game.init_graphics_component(entity_1276)
game.set_visible(entity_1276, true)
game.set_scale(entity_1276, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1276, game.enum.component.structure)
entity_1276_residences = { entity_97 }
game.add_residences(entity_1276, 'entity_1276_residences')

entity_1278 = game.create_entity()
game.add_component(entity_1278, game.enum.component.physics)
game.set_position(entity_1278, 500.000000, 50.000000, 1400.000000)
game.set_solid(entity_1278, true)
game.set_half_height(entity_1278, 50.000000)
game.add_component(entity_1278, game.enum.component.health)
game.buff(entity_1278, 2000)
game.sub_health(entity_1278, 0)
game.add_defense(entity_1278, 13)
game.set_regen(entity_1278, 1)
game.set_alive(entity_1278, true)
game.add_component(entity_1278, game.enum.component.graphics)
game.set_mesh(entity_1278, 'cube.mesh')
game.set_material(entity_1278, 'colour/brown')
game.set_manual_scaling(entity_1278, true)
game.init_graphics_component(entity_1278)
game.set_visible(entity_1278, true)
game.set_scale(entity_1278, 50.000000, 50.000000, 50.000000)
game.add_component(entity_1278, game.enum.component.structure)
entity_1278_residences = { entity_229 }
game.add_residences(entity_1278, 'entity_1278_residences')

 -- TASKS: --


 -- AUXILIARY VARIABLES TO BE DELETED:
to_be_deleted = {
'entity_0', 
'entity_1', 'entity_2', 'entity_3', 'entity_4', 'entity_5', 'entity_6', 'entity_7', 'entity_8', 'entity_9', 'entity_10', 
'entity_11', 'entity_12', 'entity_13', 'entity_14', 'entity_15', 'entity_16', 'entity_17', 'entity_18', 'entity_19', 'entity_20', 
'entity_21', 'entity_22', 'entity_23', 'entity_24', 'entity_25', 'entity_26', 'entity_27', 'entity_28', 'entity_29', 'entity_30', 
'entity_31', 'entity_32', 'entity_33', 'entity_34', 'entity_35', 'entity_36', 'entity_37', 'entity_38', 'entity_39', 'entity_40', 
'entity_41', 'entity_42', 'entity_43', 'entity_44', 'entity_45', 'entity_46', 'entity_47', 'entity_48', 'entity_49', 'entity_50', 
'entity_51', 'entity_52', 'entity_53', 'entity_54', 'entity_55', 'entity_56', 'entity_57', 'entity_58', 'entity_59', 'entity_60', 
'entity_61', 'entity_62', 'entity_63', 'entity_64', 'entity_65', 'entity_66', 'entity_67', 'entity_68', 'entity_69', 'entity_70', 
'entity_71', 'entity_72', 'entity_73', 'entity_74', 'entity_75', 'entity_76', 'entity_77', 'entity_78', 'entity_79', 'entity_80', 
'entity_81', 'entity_82', 'entity_83', 'entity_84', 'entity_85', 'entity_86', 'entity_87', 'entity_88', 'entity_89', 'entity_90', 
'entity_91', 'entity_92', 'entity_93', 'entity_94', 'entity_95', 'entity_96', 'entity_97', 'entity_98', 'entity_99', 'entity_100', 
'entity_101', 'entity_102', 'entity_103', 'entity_104', 'entity_105', 'entity_106', 'entity_107', 'entity_108', 'entity_109', 'entity_110', 
'entity_111', 'entity_112', 'entity_113', 'entity_114', 'entity_115', 'entity_116', 'entity_117', 'entity_118', 'entity_119', 'entity_120', 
'entity_121', 'entity_122', 'entity_123', 'entity_124', 'entity_125', 'entity_126', 'entity_127', 'entity_128', 'entity_129', 'entity_130', 
'entity_131', 'entity_132', 'entity_133', 'entity_134', 'entity_135', 'entity_136', 'entity_137', 'entity_138', 'entity_139', 'entity_140', 
'entity_141', 'entity_142', 'entity_143', 'entity_144', 'entity_145', 'entity_146', 'entity_147', 'entity_148', 'entity_149', 'entity_150', 
'entity_151', 'entity_152', 'entity_153', 'entity_154', 'entity_155', 'entity_156', 'entity_157', 'entity_158', 'entity_159', 'entity_160', 
'entity_161', 'entity_162', 'entity_163', 'entity_164', 'entity_165', 'entity_166', 'entity_167', 'entity_168', 'entity_169', 'entity_170', 
'entity_171', 'entity_172', 'entity_173', 'entity_174', 'entity_175', 'entity_176', 'entity_177', 'entity_178', 'entity_179', 'entity_180', 
'entity_181', 'entity_182', 'entity_183', 'entity_184', 'entity_185', 'entity_186', 'entity_187', 'entity_188', 'entity_189', 'entity_190', 
'entity_191', 'entity_192', 'entity_193', 'entity_194', 'entity_195', 'entity_196', 'entity_197', 'entity_198', 'entity_199', 'entity_200', 
'entity_201', 'entity_202', 'entity_203', 'entity_204', 'entity_205', 'entity_206', 'entity_207', 'entity_208', 'entity_209', 'entity_210', 
'entity_211', 'entity_212', 'entity_213', 'entity_214', 'entity_215', 'entity_216', 'entity_217', 'entity_218', 'entity_219', 'entity_220', 
'entity_221', 'entity_222', 'entity_223', 'entity_224', 'entity_225', 'entity_226', 'entity_227', 'entity_228', 'entity_229', 'entity_230', 
'entity_231', 'entity_232', 'entity_233', 'entity_234', 'entity_235', 'entity_236', 'entity_237', 'entity_238', 'entity_239', 'entity_240', 
'entity_241', 'entity_242', 'entity_243', 'entity_244', 'entity_245', 'entity_246', 'entity_247', 'entity_248', 'entity_249', 'entity_250', 
'entity_251', 'entity_252', 'entity_253', 'entity_254', 'entity_255', 'entity_1187', 'entity_1188', 'entity_1189', 'entity_1190', 'entity_1191', 
'entity_1192', 'entity_1193', 'entity_1194', 'entity_1195', 'entity_1196', 'entity_1197', 'entity_1198', 'entity_1199', 'entity_1200', 'entity_1201', 
'entity_1202', 'entity_1203', 'entity_1204', 'entity_1205', 'entity_1206', 'entity_1207', 'entity_1208', 'entity_1209', 'entity_1210', 'entity_1211', 
'entity_1212', 'entity_1213', 'entity_1214', 'entity_1215', 'entity_1216', 'entity_1217', 'entity_1218', 'entity_1219', 'entity_1220', 'entity_1221', 
'entity_1222', 'entity_1223', 'entity_1224', 'entity_1225', 'entity_1226', 'entity_1227', 'entity_1228', 'entity_1229', 'entity_1230', 'entity_1231', 
'entity_1232', 'entity_1233', 'entity_1234', 'entity_1235', 'entity_1236', 'entity_1237', 'entity_1238', 'entity_1239', 'entity_1240', 'entity_1241', 
'entity_1242', 'entity_1243', 'entity_1244', 'entity_1245', 'entity_1246', 'entity_1247', 'entity_1248', 'entity_1249', 'entity_1250', 'entity_1251', 
'entity_1252', 'entity_1253', 'entity_1254', 'entity_1255', 'entity_1256', 'entity_1257', 'entity_1258', 'entity_1259', 'entity_1260', 'entity_1261', 
'entity_1262', 'entity_1263', 'entity_1264', 'entity_1265', 'entity_1266', 'entity_1267', 'entity_1268', 'entity_1269', 'entity_1270', 'entity_1271', 
'entity_1272', 'entity_1273', 'entity_1274', 'entity_1275', 'entity_1276', 'entity_1278', }