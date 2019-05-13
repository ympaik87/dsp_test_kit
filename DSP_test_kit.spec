# -*- mode: python -*-

block_cipher = None


a = Analysis(['DSP_test_kit.py'],
             pathex=['F:\\dsp_test_kit'],
             binaries=[('dsp/coder_lib/Coder_RT_PCR_analyzer_v2_1/Coder_RT_PCR_analyzer_v2_1.dll',
                        'dsp/coder_lib/Coder_RT_PCR_analyzer_v2_1'),
                        ('dsp/coder_lib/AutoBaseline_v1/AutoBaseline_v1.dll',
                        'dsp/coder_lib/AutoBaseline_v1'),
                        ('dsp/coder_lib/AutoBaseline_v2/AutoBaseline_v2.dll',
                        'dsp/coder_lib/AutoBaseline_v2')],
             datas=[('ver_array.csv', '.')],
             hiddenimports=[],
             hookspath=[],
             runtime_hooks=[],
             excludes=[],
             win_no_prefer_redirects=False,
             win_private_assemblies=False,
             cipher=block_cipher,
             noarchive=False)

def get_pandas_path():
   import pandas
   pandas_path = pandas.__path__[0]
   return pandas_path
dict_tree = Tree(get_pandas_path(), prefix='pandas', excludes=["*.pyc"])
a.datas += dict_tree
a.binaries = filter(lambda x: 'pandas' not in x[0], a.binaries)

pyz = PYZ(a.pure, a.zipped_data,
             cipher=block_cipher)
exe = EXE(pyz,
          a.scripts,
          [],
          exclude_binaries=True,
          name='DSP_test_kit',
          debug=False,
          bootloader_ignore_signals=False,
          strip=False,
          upx=True,
          console=True )
coll = COLLECT(exe,
               a.binaries,
               a.zipfiles,
               a.datas,
               strip=False,
               upx=True,
               name='DSP_test_kit')
