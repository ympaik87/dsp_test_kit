from tkinter import (Label, Frame, IntVar, TOP, W, YES, ttk, StringVar, Canvas,
                     HORIZONTAL)


class CrosstalkDropdown(Frame):
    def __init__(self, tab, style, dye_li):
        Frame.__init__(self, tab)
        self.tab = tab
        self.number = 3
        self.style = style
        self.dye_li = dye_li
        self.initUI()

    def initUI(self):
        self.frameTwo = Frame(self.tab)
        self.frameTwo.grid(row=0, column=0)

        self.canvas = Canvas(self.frameTwo)
        self.listFrame = Frame(self.canvas)

        self.initialize()
        self.put_text()
        self.divider()
        self.choice_algorithm()
        self.single_well_analysis()

    def initialize(self):
        # Dropdown Menu
        optionList = ['Dye']
        for dye in self.dye_li:
            for temp_sub in ['_L', '_H']:
                optionList.append(dye + temp_sub)
        self.entry_li = []
        for i in range(self.number):
            dropVar1 = StringVar()
            dropVar1.set('Dye')  # default choice
            dropMenu1 = ttk.OptionMenu(self.tab, dropVar1, *optionList)
            dropMenu1.config(width=13)
            dropMenu1.grid(column=1, row=i+2, padx=10)

            dropVar2 = StringVar()
            dropVar2.set('Dye')  # default choice
            dropMenu2 = ttk.OptionMenu(self.tab, dropVar2, *optionList)
            dropMenu2.config(width=13)
            dropMenu2.grid(column=3, row=i+2, padx=10)
            ct_drfu = ttk.Entry(self.tab, width=8)
            ct_drfu.insert(0, 0)
            ct_drfu.grid(row=i+2, column=4, padx=10)
            ct_thrd = ttk.Entry(self.tab, width=8)
            ct_thrd.insert(0, 0)
            ct_thrd.grid(row=i+2, column=5)
            self.entry_li.append([dropVar1, dropVar2, ct_drfu, ct_thrd])

    def divider(self):
        blank = Label(self.tab, text='', width=16)
        blank.grid(row=5, column=1, columnspan=2)
        ttk.Separator(self.tab, orient=HORIZONTAL).grid(row=6, columns=1,
                                                        columnspan=10,
                                                        sticky='we')
        blank = Label(self.tab, text='', width=16)
        blank.grid(row=11, column=1, columnspan=2)
        ttk.Separator(self.tab, orient=HORIZONTAL).grid(row=12, columns=1,
                                                        columnspan=10,
                                                        sticky='we')

    def put_text(self):
        label = Label(self.tab, text='CROSSTALK')
        label.grid(row=0, column=0)
        label = Label(self.tab, text='Target 1 (from)')
        label.grid(row=1, column=1)
        label = Label(self.tab, text='Target 2 (to)')
        label.grid(row=1, column=3)
        label = Label(self.tab, text='DRFU')
        label.grid(row=1, column=4)
        label = Label(self.tab, text='Ct Thrd')
        label.grid(row=1, column=5)
        for i in range(self.number):
            label = ttk.Label(self.tab, text=f'crosstalk {i+1}',
                              justify="left")
            label.grid(row=i+2, column=0)
            label = ttk.Label(self.tab, text='➜', justify='left')
            label.grid(row=i+2, column=2)

    def get_entry(self):
        return self.entry_li, self.algoritm_entry_li, self.singlewell_entry_li

    def product_selection(self):
        label = Label(self.tab, text='제품별 알고리즘')
        label.grid(row=10, column=0, columnspan=2)
        products = ['Defualt', 'Defualt', 'GI-V (cross-talk)', 'GI-BI (2-CR)',
                    'GI-P (Q670 PC)']
        product_choice = StringVar()
        product_choice.set('Default')  # default choice
        dropMenu1 = ttk.OptionMenu(self.tab, product_choice, *products)
        dropMenu1.config(width=18)
        dropMenu1.grid(column=2, row=10, padx=10, columnspan=2)
        return product_choice

    def _algorithm_dropdown(self, rw, col, txt):
        label = Label(self.tab, text=txt)
        label.grid(row=rw, column=col, columnspan=2)

        algorithm_li = ['Default (latest ver.)', 'Default (latest ver.)',
                        'Old ver.']
        algorithm_choice = StringVar()
        algorithm_choice.set('Default (latest ver.)')  # default choice
        dropMenu1 = ttk.OptionMenu(self.tab, algorithm_choice, *algorithm_li)
        dropMenu1.config(width=18)
        dropMenu1.grid(column=col+2, row=rw, padx=10, columnspan=2)

        sample_kind_li = ['All', 'All', 'PC only', 'Sample only']
        sample_choice = StringVar()
        sample_choice.set('All')
        dropMenu2 = ttk.OptionMenu(self.tab, sample_choice, *sample_kind_li)
        dropMenu2.config(width=18)
        dropMenu2.grid(column=col+4, row=rw, padx=10, columnspan=2)
        return [algorithm_choice, sample_choice]

    def choice_algorithm(self):
        label = Label(self.tab, text='Algorithm'.upper())
        label.grid(row=7, column=0)
        absd_corrector_switch = self._algorithm_dropdown(
            8, 0, '과도한 CR에 대한 보정')
        asymm_sigfit_switch = self._algorithm_dropdown(9, 0, 'Ct값 보정')
        product_choice = self.product_selection()
        self.algoritm_entry_li = [absd_corrector_switch, asymm_sigfit_switch,
                                  product_choice]

    def single_well_analysis(self):
        label = Label(self.tab, text='single well'.upper())
        label.grid(row=13, column=0)
        check_single = Checkbar(self.tab, ['On'], self.style)
        check_single.grid(row=13, column=1)

        label = Label(self.tab, text='Dye')
        label.grid(row=14, column=0)
        dye_choice = StringVar()
        dye_choice.set('Choose dye')  # default choice
        dye_options = ['Choose dye']
        dye_options.extend(self.dye_li)
        dropMenu1 = ttk.OptionMenu(self.tab, dye_choice, *dye_options)
        dropMenu1.config(width=14)
        dropMenu1.grid(column=1, row=14, padx=10, columnspan=2)

        label = Label(self.tab, text='Well')
        label.grid(row=14, column=3)
        well_entry = ttk.Entry(self.tab, width=8)
        well_entry.insert(0, '')
        well_entry.grid(row=14, column=4)
        self.singlewell_entry_li = [check_single.vars[0], dye_choice,
                                    well_entry]


class Checkbar(Frame):
    def __init__(self, parent, picks, style, side=TOP, anchor=W):
        Frame.__init__(self, parent)
        self.vars = []
        for pick in picks:
            var = IntVar()
            chk = ttk.Checkbutton(self, text=pick, variable=var)
            chk.pack(side=side, anchor=anchor, expand=YES)
            self.vars.append(var)


class DspEntry:
    def __init__(self, root, value_df, dye_li, tabs, style, crosstalk_tab):
        self.value_df = value_df
        self.root = root
        self.dye_li = dye_li
        self.tabs = tabs
        self.crosstalk_tab = crosstalk_tab

    def dyeless_entries(self, row, column, text, key1, key2, end_cycle=None):
        lbl = Label(self.root, text=text, width=8)
        lbl.grid(row=row, column=column)
        if end_cycle:
            start_entry = ttk.Entry(self.root, width=8)
            start_entry.insert(0, self.value_df[key1][key2])
            start_entry.grid(row=row, column=column+1)
            end_entry = ttk.Entry(self.root, width=8)
            end_entry.insert(0, self.value_df[key1][end_cycle])
            end_entry.grid(row=row, column=column+2)
            entry = [start_entry, end_entry]
        else:
            entry = ttk.Entry(self.root, width=8)
            entry.insert(0, self.value_df[key1][key2])
            entry.grid(row=row, column=column+1)
        return entry

    def dye_entries(self, row, text, key, col_start=1):
        label = Label(self.root, text=text, width=8)
        label.grid(row=row, column=col_start, columnspan=col_start+1)
        entry_li = []
        col_start += 2
        for dye in self.dye_li:
            entry = ttk.Entry(self.root, width=8)
            entry.insert(0, self.value_df[key][dye])
            entry.grid(row=row, column=col_start)
            entry_li.append(entry)
            col_start += 1
        return entry_li

    def tab_entries(self, row, key_li, text, col_start=3):
        res_li = []
        for tab in self.tabs:
            col = col_start
            label = Label(tab, text=text, width=16)
            label.grid(row=row, column=1, columnspan=2)
            key = key_li[self.tabs.index(tab)]
            entry_li = []
            for dye in self.dye_li:
                entry = ttk.Entry(tab, width=8)
                entry.insert(0, self.value_df[key][dye])
                entry.grid(row=row, column=col)
                entry_li.append(entry)
                col += 1
            res_li.append(entry_li)
        return res_li

    def blank(self, row, col, is_tabs=False, text=''):
        if is_tabs and text:
            for tab in self.tabs:
                blank = Label(tab, text=text, width=16)
                blank.grid(row=row, column=col, columnspan=2)
        elif is_tabs:
            for tab in self.tabs:
                blank = Label(tab, text=text, width=8)
                blank.grid(row=row, column=col)
        else:
            blank = Label(self.root, text=text, width=8)
            blank.grid(row=row, column=col)

    def dye_labels(self, dye_label_li, row, col_start=3, tab=None):
        for dye in dye_label_li:
            if tab:
                label = Label(tab, text=dye, width=8)
            else:
                label = Label(self.root, text=dye, width=8)
            label.grid(row=row, column=col_start)
            col_start += 1
