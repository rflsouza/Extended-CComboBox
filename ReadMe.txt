========================================================================
MFC win32 Extended-CComboBox C++
========================================================================

A combobox control which shows a drop down window to assist the user.

This is a copy from _Flaviu  [codeproject](https://www.codeproject.com/Articles/187753/Extended-CComboBox). 


Changes:
- (add) Find using character us-ASC, ignore accenture.  
- (add) Setting the display rectangle to List Tooltip. 
  Use: m_Combo1.SetListTooltip(,,,int nMaxTipWidth = SHRT_MAX)
  Reference: https://docs.microsoft.com/en-us/windows/desktop/controls/implement-multiline-tooltips
- (change) In mode dropdown, search text (all words) in any part of the string.
- (fix) Leak in destroy object.

References:
[Microsoft] https://docs.microsoft.com/en-us/windows/desktop/controls/tooltip-controls
[Using the CComboBox control](https://www.codeproject.com/Articles/762/%2FArticles%2F762%2FUsing-the-CComboBox-control)
[MFC - Combo Boxes](https://www.tutorialspoint.com/mfc/mfc_combo_boxes.htm)
[AutoComplete without IAutoComplete](https://www.codeproject.com/Articles/2607/AutoComplete-without-IAutoComplete)
