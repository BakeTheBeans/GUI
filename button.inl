#if(BUTTON_4)
template class Button<PlainTexture>;
template class Button<FileTexture>;
template class Button<CancelTexture>;
template class Button<EditTexture>;
template class Button<MenuTexture>;
/*
template class Button<NavigateTexture>;
template class Button<NextTexture>;
template class Button<SaveTexture>;
template class Button<SettingsTexture>;
template class Button<StopTexture>;
template class Button<ToolsTexture>;
template class Button<BackTexture>;
*/
#endif


#if(BUTTON_3)
template class Button<ArcIcon>;
template class Button<AttachmentIcon>;
template class Button<BoldIcon>;
template class Button<CircleIcon>;
template class Button<FileIcon>;
template class Button<FontIcon>;
template class Button<HomeIcon>;
template class Button<ItalicIcon>;
template class Button<LineIcon>;
template class Button<PencilIcon>;
template class Button<PickColorIcon>;
template class Button<PolygonIcon>;
template class Button<SearchIcon>;
template class Button<SquareIcon>;
template class Button<TrashIcon>;
#endif

/*
typedef Button<void> PlainButton;
typedef Button<ArcIcon> ArcIconButton;
typedef Button<AttachmentIcon> AttachmentIconButton;
typedef Button<BoldIcon> BoldIconButton;
typedef Button<CircleIcon> CircleIconButton;
typedef Button<FileIcon> FileIconButton;
typedef Button<FontIcon> FontIconButton;
typedef Button<HomeIcon> HomeIconButton;
typedef Button<ItalicIcon> ItalicIconButton;
typedef Button<LineIcon> LineIconButton;
typedef Button<PencilIcon> PencilIconButton;
typedef Button<PickColorIcon> PickColorIconButton;
typedef Button<PolygonIcon> PolygonIconButton;
typedef Button<SearchIcon> SearchIconButton;
typedef Button<SquareIcon> SquareIconButton;
typedef Button<TrashIcon> TrashIconButton;

*/
