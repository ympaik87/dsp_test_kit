from matplotlib.backends.backend_wxagg import FigureCanvasWxAgg
import wx


class DspFigCanvas(FigureCanvasWxAgg):
    def __init__(self, parent, id, figure, _dsp=None):
        FigureCanvasWxAgg.__init__(self, parent, id, figure)
        self.parent = parent
        self.dsp = _dsp

    def _onRightButtonUp(self, evt):
        FigureCanvasWxAgg._onRightButtonUp(self, evt)
        x = evt.GetX()
        y = self.figure.bbox.height - evt.GetY()
        width = self.figure.bbox.width/3
        height = self.figure.bbox.height/2
        if 0 <= x < width:
            self.coordinate_x = 1
        elif width <= x < width*2:
            self.coordinate_x = 2
        else:
            self.coordinate_x = 3
        if 0 <= y < height:
            self.coordinate_y = 2
        else:
            self.coordinate_y = 1
        self.Bind(wx.EVT_CONTEXT_MENU, self.on_context)

    def on_context(self, event):
        if not hasattr(self, 'popup_id'):
            self.popup_id = wx.NewId()
            self.popup_id2 = wx.NewId()
            self.Bind(wx.EVT_MENU, self.on_save_fig, id=self.popup_id)
            self.Bind(wx.EVT_MENU, self.on_save_fig_all, id=self.popup_id2)
        menu = wx.Menu()
        menu.Append(self.popup_id, 'Copy this figure')
        menu.Append(self.popup_id2, 'Copy all figures')

        self.PopupMenu(menu)
        menu.Destroy()

    def on_save_fig(self, event):
        self.copy_to_clipboard(event)

    def on_save_fig_all(self, event):
        self.copy_to_clipboard(event, is_all=True)

    def copy_to_clipboard(self, event=None, is_all=False):
        "copy bitmap of canvas to system clipboard"
        bmp_obj = wx.BitmapDataObject()
        if is_all:
            bmp_obj.SetBitmap(self.bitmap)
        else:
            if self.dsp is None:
                wx.MessageBox('Figures are empty', 'Warning',
                              wx.OK | wx.ICON_WARNING)
                return
            figure = self.dsp.get_subax(self.coordinate_x, self.coordinate_y)
            panel = wx.Panel(self.parent)
            canvas = FigureCanvasWxAgg(panel, -1, figure)
            canvas.draw()
            bmp_obj.SetBitmap(canvas.bitmap)

        if not wx.TheClipboard.IsOpened():
            open_success = wx.TheClipboard.Open()
            if open_success:
                wx.TheClipboard.SetData(bmp_obj)
                wx.TheClipboard.Close()
                wx.TheClipboard.Flush()
