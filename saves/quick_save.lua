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
entity_1186 = game.create_entity()
game.add_component(entity_1186, game.enum.component.physics)
game.set_position(entity_1186, 727.225403, 27.008251, 727.225403)
game.set_solid(entity_1186, false)
game.set_half_height(entity_1186, 27.008251)
game.add_component(entity_1186, game.enum.component.health)
game.buff(entity_1186, 1000)
game.sub_health(entity_1186, 0)
game.add_defense(entity_1186, 8)
game.set_regen(entity_1186, 1)
game.set_alive(entity_1186, true)
game.add_component(entity_1186, game.enum.component.ai)
game.set_blueprint(entity_1186, 'ogre')
game.set_state(entity_1186, 1)
game.set_faction(entity_1186, 0)
game.add_component(entity_1186, game.enum.component.graphics)
game.set_mesh(entity_1186, 'ogrehead.mesh')
game.set_material(entity_1186, 'Ogre')
game.init_graphics_component(entity_1186)
game.set_visible(entity_1186, true)
game.add_component(entity_1186, game.enum.component.movement)
game.set_speed(entity_1186, 0.500000)
game.add_component(entity_1186, game.enum.component.pathfinding)
game.set_pathfinding_blueprint(entity_1186, 'ogre')
game.add_component(entity_1186, game.enum.component.task_handler)
game.add_possible_task(entity_1186, 1)
game.add_possible_task(entity_1186, 2)

entity_1187 = game.create_entity()
game.add_component(entity_1187, game.enum.component.task)
game.set_task_source(entity_1187, entity_1186)
game.set_task_target(entity_1187, entity_255)
game.set_task_type(entity_1187, 1)

entity_1188 = game.create_entity()
game.add_component(entity_1188, game.enum.component.task)
game.set_task_source(entity_1188, entity_1186)
game.set_task_target(entity_1188, entity_15)
game.set_task_type(entity_1188, 1)

entity_1189 = game.create_entity()
game.add_component(entity_1189, game.enum.component.task)
game.set_task_source(entity_1189, entity_1186)
game.set_task_target(entity_1189, entity_240)
game.set_task_type(entity_1189, 1)

entity_1190 = game.create_entity()
game.add_component(entity_1190, game.enum.component.task)
game.set_task_source(entity_1190, entity_1186)
game.set_task_target(entity_1190, entity_0)
game.set_task_type(entity_1190, 1)

 -- TASKS: --
game.add_task(entity_1186, entity_1187)
game.add_task(entity_1186, entity_1188)
game.add_task(entity_1186, entity_1189)
game.add_task(entity_1186, entity_1190)


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
'entity_251', 'entity_252', 'entity_253', 'entity_254', 'entity_255', 'entity_1186', 'entity_1187', 'entity_1188', 'entity_1189', 'entity_1190', 
}