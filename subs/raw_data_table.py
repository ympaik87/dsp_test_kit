from subs.data_table import DspDataTable, DataTable


class RawDataTable(DspDataTable):
    def __init__(self, parent, dye_li):
        super().__init__(parent, dye_li)
        self.panel = parent
        self.dye_li = dye_li
        self.choice_li = self.get_choice_li()

    def set_table(self, df_list, choice):
        return DataTable(df_list[choice].fillna('N/A'))

    def get_choice_li(self):
        li = ['EPR', 'EPR+SD', 'RV', 'RV+SD']
        li1 = [i + ' Samples only' for i in li]
        li2 = [i + ' PCs only' for i in li]
        return li + li1 + li2
