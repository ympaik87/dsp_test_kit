import pandas as pd
import numpy as np
import wx
import wx.grid


class DataTable(wx.grid.GridTableBase):
    def __init__(self, data=None):
        wx.grid.GridTableBase.__init__(self)
        self.headerRows = 1
        self.EVEN_ROW_COLOUR = '#CCE6FF'
        self.GRID_LINE_COLOUR = '#ccc'
        if data is None:
            data = pd.DataFrame()
        self.data = data

    def GetNumberRows(self):
        return len(self.data)

    def GetNumberCols(self):
        return len(self.data.columns)

    def GetValue(self, row, col):
        return self.data.iloc[row, col]

    def SetValue(self, row, col, value):
        self.data.iloc[row, col] = value

    def GetColLabelValue(self, col):
        return str(self.data.columns[col])

    def GetRowLabelValue(self, row):
        return str(self.data.index[row])

    def GetTypeName(self, row, col):
        return wx.grid.GRID_VALUE_STRING

    def GetAttr(self, row, col, prop):
        attr = wx.grid.GridCellAttr()
        if row % 2 == 1:
            attr.SetBackgroundColour(self.EVEN_ROW_COLOUR)
        return attr


class DspDataTable:
    def __init__(self, parent, dye_li):
        self.panel = parent
        self.dye_li = dye_li
        self.data_list = ['df_array', 'end_rfu', 'R2_array', 'R_p2_array']
        self.choice_li = ['df', 'RFU', 'Rp2']

    def set_table(self, dict, choice):
        df = self.convert_dict_to_df(dict, choice)
        return DataTable(df)

    def convert_dict_to_df(self, dict, choice):
        well_ind = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H']
        df_index = []
        for r in range(8):
            for c in range(12):
                df_index.append(f'{well_ind[r]}{c+1}')
        idx = self.data_list[choice - 1]
        data_dict = dict[idx]
        df_dict = {}
        for dye in self.dye_li:
            for temp in data_dict.keys():
                row_li = []
                for well in df_index:
                    if well in data_dict[temp][dye].keys():
                        val = data_dict[temp][dye][well]
                        if isinstance(val, np.ndarray):
                            row_li.append(round(val.item(), 2))
                        else:
                            row_li.append(round(val, 2))
                    else:
                        row_li.append('N/A')
                if 'Cal' in dye:
                    dye_label = dye[0] + '610'
                elif '670' in dye:
                    dye_label = dye[0] + '670'
                elif '705' in dye:
                    dye_label = dye[0] + '705'
                else:
                    dye_label = dye
                col_name = dye_label + '/' + temp.split(' ')[0][0]
                if len(row_li) > 0:
                    df_dict[col_name] = row_li
        df = pd.DataFrame(df_dict)
        df.index = df_index
        return df

    def data_selection(self):
        label_data = wx.StaticText(
            self.panel, wx.ID_ANY, "Parameters", wx.DefaultPosition,
            wx.DefaultSize, 0)
        label_data.Wrap(-1)

        choice = wx.Choice(
            self.panel, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize,
            self.choice_li, 0)
        choice.SetSelection(0)

        return label_data, choice
