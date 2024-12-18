#include <std_include.hpp>

#include "menus.hpp"
#include "command.hpp"
#include "console.hpp"
#include "game/game.hpp"

#include "loader/component_loader.hpp"
#include "utils/string.hpp"

namespace menus
{
    game::ItemFloatExpressionEntry itemFloatExpressions[19] = 
    {
        { 0, "rect", "x" },
        { 1, "rect", "y" },
        { 2, "rect", "w" },
        { 3, "rect", "h" },
        { 4, "forecolor", "r" },
        { 5, "forecolor", "g" },
        { 6, "forecolor", "b" },
        { 7, "forecolor", "rgb" },
        { 8, "forecolor", "a" },
        { 9, "glowcolor", "r" },
        { 10, "glowcolor", "g" },
        { 11, "glowcolor", "b" },
        { 12, "glowcolor", "rgb" },
        { 13, "glowcolor", "a" },
        { 14, "backcolor", "r" },
        { 15, "backcolor", "g" },
        { 16, "backcolor", "b" },
        { 17, "backcolor", "rgb" },
        { 18, "backcolor", "a" }
    };

    const char *d[4] = 
    {
        "dvarint( \"%s\" )",
        "dvarbool( \"%s\" )",
        "dvarfloat( \"%s\" )",
        "dvarstring( \"%s\" )"
    };

    #define COMMAND_COUNT 62
    const char *commandList[COMMAND_COUNT] = 
    {
        "fadein",
        "fadeout",
        "show",
        "hide",
        "showMenu",
        "hideMenu",
        "setcolor",
        "open",
        "close",
        "closeForAllPlayers",
        "ingameopen",
        "ingameclose",
        "setbackground",
        "setItemColor",
        "focusfirst",
        "setfocus",
        "setfocusbydvar",
        "setdvar",
        "exec",
        "execnow",
        "execOnDvarStringValue",
        "execOnDvarIntValue",
        "execOnDvarFloatValue",
        "execNowOnDvarStringValue",
        "execNowOnDvarIntValue",
        "execNowOnDvarFloatValue",
        "play",
        "scriptmenuresponse",
        "scriptMenuRespondOnDvarStringValue",
        "scriptMenuRespondOnDvarIntValue",
        "scriptMenuRespondOnDvarFloatValue",
        "setPlayerData",
        "setPlayerDataSplitscreen",
        "updateMail",
        "openMail",
        "deleteMail",
        "doMailLottery",
        "resetStatsConfirm",
        "resetStatsCancel",
        "setGameMode",
        "setLocalVarBool",
        "setLocalVarInt",
        "setLocalVarFloat",
        "setLocalVarString",
        "feederTop",
        "feederBottom",
        "showGamerCard",
        "openforgametype",
        "closeforgametype",
        "statclearperknew",
        "statsetusingtable",
        "statclearbitmask",
        "kickPlayer",
        "getKickPlayerQuestion",
        "partyUpdateMissingMapPackDvar",
        "getHostMigrateQuestion",
        "makehost",
        "togglePlayerMute",
        "addFriendFromId",
        "resolveError",
        "lerp",
        "uiScript"
    };
    
    namespace
    {
        void PrintStatement(FILE *f, game::Statement_s *e, const char *name, int tabc, bool semiColon = false);
		void PrintMenuEventHandlerSet(FILE *f, game::MenuEventHandlerSet *s, const char *name, int tabc);

		char *getTabs(int t)
		{
			static char tabs[10];
			for (int i = 0;
				i < t && i < 10; i++)
				*(tabs + i) = '\t';
			*(tabs + t) = 0;
			return tabs;
		}

		void PrintString(FILE *f, const char *str, const char *name, int tabc)
		{
			if (str && *str)
					fprintf(f, "%s%s \"%s\"\n", getTabs(tabc), name, str);
		}

		#define VEC4(v) (v[0] > 0 || v[1] > 0 || v[2] > 0 || v[3] > 0)

		void PrintColor(FILE *file, float *color, const char *name, int tabc)
		{
			if (color[0] > 0.0f || color[1] > 0.0f || color[2] > 0.0f || color[3] > 0.0f)
				fprintf(file, "%s%s %g %g %g %g\n", getTabs(tabc), name, color[0], color[1], color[2], color[3]);
		}

		void PrintRect(FILE *file, game::rectDef_s rect, const char *name, int tabc)
		{
			fprintf(file, "%s%s %g %g %g %g %i %i\n", getTabs(tabc), name, rect.x, rect.y, rect.w, rect.h, rect.horzAlign, rect.vertAlign);
		}

		void PrintFloat(FILE *file, float value, const char *name, int tabc)
		{
			if (value) fprintf(file, "%s%s %g\n", getTabs(tabc), name, value);
		}

		void PrintInt(FILE *file, int value, const char *name, int tabc)
		{
			if (value) fprintf(file, "%s%s %i\n", getTabs(tabc), name, value);
		}

		void PrintBool(FILE *file, bool value, const char *name, int tabCount)
		{
			if (value) fprintf(file, "%s%s\n", getTabs(tabCount), name);
		}

		// case sensitive
		bool replaceAll(std::string& str, const std::string& from, const std::string& to) {
			bool found = false;
			if(from.empty())
				return false;
			size_t start_pos = 0;
			while((start_pos = str.find(from, start_pos)) != std::string::npos) {
				found = true;
				str.replace(start_pos, from.length(), to);
				start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
			}
			return found;
		}

		bool replace(std::string& str, const std::string& from, const std::string& to) {
			size_t start_pos = str.find(from);
			if(start_pos == std::string::npos)
				return false;
			str.replace(start_pos, from.length(), to);
			return true;
		}

		bool _replace(std::string& str, const std::string& from, const std::string& to) {
			std::string t1(str);
			std::string t2(from);
			for (int i = 0; i < from.length(); i++)
				t2[i] = tolower(from[i]);
			for (int i = 0; i < str.length(); i++)
				t1[i] = tolower(str[i]);
			size_t start_pos = t1.find(t2);
			if (start_pos == std::string::npos)
				return false;
			str.replace(start_pos, from.length(), to);
			return true;
		}

		bool _replaceAll(std::string& str, const std::string& from, const std::string& to) {
			while (_replace(str, from, to))
				continue;
			return false;
		}

		void formatCMD(std::string& str)
		{
			for (int i = 0; i < COMMAND_COUNT; i++)
			{
				std::string rep("\"");
				rep.append(commandList[i]).append("\" (");
				std::string tem(commandList[i]);
				tem.append("(");
				_replaceAll(str, rep, tem);
				rep.clear();
				rep.append("\"").append(commandList[i]).append("\"");
				_replaceAll(str, rep, commandList[i]);
			}
		}

		std::string format(const char *input, int tabc)
		{
			std::string tabs = getTabs(tabc);
			std::string output(tabs);
			output.append(input).append("\n");	// needed to mark the end of the script
			replace(output, "\t; ", "\t");
			replace(output, (tabs + "\n"), "");
			replace(output, " ; \n", ";\n");
			replace(output, " \n", ";\n");
			replaceAll(output, " ; ", ";\n" + tabs);
			//replaceAll(output, ") ( ) ", ") ");	// not sure why it does this
			formatCMD(output);	// <- NEEDED in order to load them without errors
									// remove all quotes on commands or maybe i should just strip all quotes..
									// if not then strip from commands
			//replaceAll(output, "\"", "");
			_replaceAll(output, "\"self\"", "self");		// unquote self
			_replaceAll(output, "\"forecolor\"", "forecolor");	// unquote forecolor
			_replaceAll(output, "\"backcolor\"", "backcolor");	// unquote backcolor
			_replaceAll(output, "\"bordercolor\"", "bordercolor");	//unquote bordercolor
			return output;
		}

		std::string safetext(const char *input)
		{
			std::string output(input);
			_replaceAll(output, "\\", "\\\\");
			return output;
		}

		void PrintSetLocalVarData(FILE *f, game::EventType type, game::SetLocalVarData *e, int tabc)
		{
			if ( e )
			{
				const char *cmd;
				switch (type)
				{
				case game::EVENT_SET_LOCAL_VAR_BOOL: cmd = "setLocalVarBool"; break;
				case game::EVENT_SET_LOCAL_VAR_INT: cmd = "setLocalVarInt"; break;
				case game::EVENT_SET_LOCAL_VAR_FLOAT: cmd = "setLocalVarFloat"; break;
				case game::EVENT_SET_LOCAL_VAR_STRING: cmd = "setLocalVarString"; break;
				}

				fprintf(f, "%s%s \"%s\"", getTabs(tabc), cmd, e->localVarName);
				PrintStatement(f, e->expression, NULL, tabc + 1, true);
			}
		}

		void PrintConditionalScript(FILE *f, game::ConditionalScript *s, int tabc)
		{
			if ( s )
			{
				fprintf(f, "%sif", getTabs(tabc));
				PrintStatement(f, s->eventExpression, NULL, tabc);
				fprintf(f, "%s{\n", getTabs(tabc));
				PrintMenuEventHandlerSet(f, s->eventHandlerSet, NULL, tabc);
				fprintf(f, "%s}\n", getTabs(tabc));
			}
		}

		void PrintStatement(FILE *f, game::Statement_s *e, const char *name, int tabc, bool semiColon /*= false*/)
		{
			if ( e )
			{
				const bool cleanStatements = true;	// make false to dump raw expression entries
				bool isZType = false;

				if (name) fprintf(f, "%s%s", getTabs(tabc), name);
				if (cleanStatements && e->numEntries > 0) 
					if (e->entries[0].data.op != 16/*OP_LEFTPAREN*/) 
						fputs(" (", f);

				for (int i = 0; i < e->numEntries; i++)
				{
					int type = e->entries[i].type;
					if (type == OPERATOR)
					{
						isZType = true;
						int op = e->entries[i].data.op;
						if (!cleanStatements)
							fprintf(f, " %s ", game::MenuOps[op]);
						else 
						{
							if (op < 23/*OP_FIRSTFUNCTIONCALL*/)
							{
								// if last op was OP_RIGHTPAREN and this op is OP_LEFTPAREN, skip it
								if (e->entries[i-1].data.op == 1/*OP_RIGHTPAREN*/ && op == 16/*OP_LEFTPAREN*/)
								{
									i++;
									continue;
								}

								// if last op was OP_NOT
								if (e->entries[i-1].data.op == 7/*OP_NOT*/)
									fprintf(f, "%s", game::MenuOps[op]);
								else
									fprintf(f, " %s", game::MenuOps[op]);
							}
							else if (op <= 26/*OP_STATICDVARSTRING*/ && op >= 23/*OP_STATICDVARINT*/)
							{
								i++;	// go to next op which is the dvar index in staticVars
								char res[256];
								sprintf(res, d[op-23], e->supportingData->staticDvarList.staticDvars[e->entries[i].data.operand.internals.intVal]->dvarName);
								// if previous op was OP_NOT
								if (e->entries[i-2].data.op == 7)
									fprintf(f, "%s", res);	// so it prints !var (instead of ! var)
								else fprintf(f, " %s", res);	// this one has a space to make it look nice
								i++;
							}
							// everything else (commands)
							else
							{
								// if previous op was OP_NOT
								if (e->entries[i-1].data.op == 7/*OP_NOT*/)
									fprintf(f, "%s(", game::MenuOps[op]);	// prints !func
								else fprintf(f, " %s(", game::MenuOps[op]);	// this one has a space
							}
						}
					}
					else if (type == OPERAND)
					{
						switch (e->entries[i].data.operand.dataType)
						{
						case game::VAL_INT:
							fprintf(f, " %i", e->entries[i].data.operand.internals.intVal);
							break;
						case game::VAL_FLOAT:
							fprintf(f, " %g", e->entries[i].data.operand.internals.floatVal);
							break;
						case game::VAL_STRING:
							fprintf(f, " \"%s\"", e->entries[i].data.operand.internals.stringVal);
							break;
						case game::VAL_FUNCTION:
							PrintStatement(f, e->entries[i].data.operand.internals.function, NULL, 0);
							break;
						}
					}
				}

				if (cleanStatements) 
				{
					if (isZType) fputs(" )", f);
					if (e->numEntries > 0 && e->entries[0].data.op != 16/*OP_LEFTPAREN*/) fputs(" )", f);
					if (semiColon) fputs(";", f);
				}

				if (tabc) fputs("\n", f);
			}
		}

		void PrintMenuEventHandlerSet(FILE *f, game::MenuEventHandlerSet *s, const char *name, int tabc)
		{
			if ( s )
			{
				bool formatStatement = true;
				if (name) fprintf(f, "%s%s\n%s{\n", getTabs(tabc), name, getTabs(tabc));

				for (int e = 0; e < s->eventHandlerCount; e++)
				{
					switch (s->eventHandlers[e]->eventType)
					{
					case game::EVENT_UNCONDITIONAL:
						if (formatStatement)
							fprintf(f, "%s", format(s->eventHandlers[e]->eventData.unconditionalScript, tabc + 1).c_str());
						else
							fprintf(f, "%s%s\n", getTabs(tabc+1), s->eventHandlers[e]->eventData);
						break;
					case game::EVENT_IF:
						PrintConditionalScript(f, s->eventHandlers[e]->eventData.conditionalScript, tabc + 1);
						break;
					case game::EVENT_ELSE:
						PrintMenuEventHandlerSet(f, s->eventHandlers[e]->eventData.elseScript, "else", tabc + 1);
						break;
					case game::EVENT_SET_LOCAL_VAR_BOOL:
					case game::EVENT_SET_LOCAL_VAR_INT:
					case game::EVENT_SET_LOCAL_VAR_FLOAT:
					case game::EVENT_SET_LOCAL_VAR_STRING:
						PrintSetLocalVarData(f, s->eventHandlers[e]->eventType, s->eventHandlers[e]->eventData.setLocalVarData, tabc + 1);
						break;
					default:
						break;
					}
				}
				
				if (name) fprintf(f, "%s}\n", getTabs(tabc));
			}
		}

		void PrintItemKeyHandler(FILE *f, game::ItemKeyHandler *k, const char *name, int tabc)
		{
			if ( k )
			{
				char buf[256];
				//sprintf(buf, "%s \"%s\"", name, Key_KeynumToString(k->key));
				sprintf(buf, "%s %i" //"\t// %s"
								,name
								,k->key 
								//, Key_KeynumToString(k->key)
								);
				PrintMenuEventHandlerSet(f, k->action, buf, tabc);
				PrintItemKeyHandler(f, k->next, "execKeyInt", tabc);
			}
		}

		void PrintItemFloatExpressions(FILE *f, int count, game::ItemFloatExpression *e, int tabc)
		{
			if ( e )
			{
				for (int i = 0; i < count; i++)
				{
					char name[256];
					sprintf(name, "exp %s %s", itemFloatExpressions[e[i].target].s1, itemFloatExpressions[e[i].target].s2);
					PrintStatement(f, e[i].expression, name, tabc);
				}
			}
		}

		void PrintLBColumns(FILE *f, int n, game::columnInfo_s *c, int tabc)
		{
			fprintf(f, "//%snumcol\t\t\txpos\txwidth\ttextlen\t  alignment\n", getTabs(tabc));
			fprintf(f, "%s%s %i\t\t%i\t\t%i\t\t%i\t\t  %i\n", getTabs(tabc), "columns", n, c[0].pos, c[0].width, c[0].maxChars, c[0].alignment);
			for (int i = 1; i < n; i++)
				fprintf(f, "%s\t\t\t\t%i\t\t%i\t\t%i\t\t  %i\n", getTabs(tabc), c[i].pos, c[i].width, c[i].maxChars, c[i].alignment);
		}

		void DumpListBox(FILE *f, game::listBoxDef_s *l, int tabc)
		{
			PrintColor(f, l->selectBorder, "selectBorder", tabc);
			if (l->selectIcon)
				PrintString(f, l->selectIcon->name, "selectIcon", tabc);
			PrintFloat(f, l->elementWidth, "elementWidth", tabc);
			PrintFloat(f, l->elementHeight, "elementHeight", tabc);
			PrintInt(f, l->elementStyle, "elementtype", tabc);
			PrintLBColumns(f, l->numColumns, l->columnInfo, tabc);
			PrintBool(f, l->noScrollBars, "noscrollbars", tabc);
			PrintBool(f, l->notselectable, "notselectable", tabc);
			PrintBool(f, l->usePaging, "usepaging", tabc);
			PrintMenuEventHandlerSet(f, l->onDoubleClick, "doubleClick", tabc);
		}

		void DumpMultiDef(FILE *f, game::multiDef_s *m, int tabc)
		{
			if (m->strDef)
				fprintf(f, "%s%s {", getTabs(tabc), "dvarStrList");
			else
				fprintf(f, "%s%s {", getTabs(tabc), "dvarFloatList");

			for (int i = 0; i < m->count; i++)
			{
				fprintf(f, " \"%s\"", m->dvarList[i]);
				if (m->strDef)
					fprintf(f, " \"%s\"", m->dvarStr[i]);
				else
					fprintf(f, " %g", m->dvarValue[i]);
			}
			fputs(" }\n", f);
		}

		void PrintItemDefData(FILE *f, int type, game::itemDefData_t *d, int tabc, const char *dvar = NULL)
		{
			if ( d->data )
			{
				switch (type)
				{
				case ITEM_TYPE_LISTBOX:
					DumpListBox(f, d->listBox, tabc);
					break;
				case ITEM_TYPE_MULTI:
					DumpMultiDef(f, d->multi, tabc);
					break;
				case ITEM_TYPE_DVARENUM:
					fprintf(f, "%s%s %s %s", getTabs(tabc), "dvar", "dvarEnumList", d->enumDvarName);
					break;
				case ITEM_TYPE_NEWSTICKER:
					PrintInt(f, d->ticker->feedId, "newsfeed", tabc);
					PrintInt(f, d->ticker->speed, "speed", tabc);
					PrintInt(f, d->ticker->spacing, "spacing", tabc);
					break;
				case ITEM_TYPE_TEXTSCROLL:
					break;
				case ITEM_TYPE_EDITFIELD:
				case ITEM_TYPE_NUMERICFIELD:
				case ITEM_TYPE_VALIDFILEFIELD:
				case ITEM_TYPE_UPREDITFIELD:
				case ITEM_TYPE_YESNO:
				case ITEM_TYPE_BIND:
				case ITEM_TYPE_TEXT:
				case ITEM_TYPE_DECIMALFIELD:
				case ITEM_TYPE_EMAILFIELD:
				case ITEM_TYPE_PASSWORDFIELD:
					PrintInt(f, d->editField->maxChars, "maxChars", tabc);
					PrintInt(f, d->editField->maxCharsGotoNext, "maxCharsGotoNext", tabc);
					PrintInt(f, d->editField->maxPaintChars, "maxPaintChars", tabc);
					break;
				case ITEM_TYPE_SLIDER:
					fprintf(f, "%s%s \"%s\" %g %g %g\n", getTabs(tabc), "dvarFloat", dvar, d->editField->defVal, d->editField->minVal, d->editField->maxVal);
					break;
				default:
					break;
				}
			}
		}

		void PrintDvarTest(FILE *f, const char *dvarTest, const char *enableDvar, int dvarFlags, int tabc)
		{ 
			// should actually be (dvarFlags & value) but i've found no dvarFlags with multiple flags set. so meh.
			// the compiler ORS dvarFlags if any of these keywords are found
			const char *d;
			switch (dvarFlags)
			{
				case 0x01: d = "enableDvar"; break;
				case 0x02: d = "disableDvar"; break;
				case 0x04: d = "showDvar"; break;
				case 0x08: d = "hideDvar"; break;
				case 0x10: d = "focusDvar"; break;
			}
			PrintString(f, dvarTest, "dvarTest", tabc);
			if (enableDvar)
			{
				fprintf(f, "%s%s { %s}\n", getTabs(tabc), d, enableDvar);
			}
		}

		void PrintStaticFlags(FILE *f, int s, int tabc)
		{
			PrintBool(f, s & WINDOWSTATIC_DECORATION, "decoration", tabc);
			PrintBool(f, s & WINDOWSTATIC_HORIZONTALSCROLL, "horizontalscroll", tabc);
			PrintBool(f, s & WINDOWSTATIC_SCREENSPACE, "screenSpace", tabc);
			PrintBool(f, s & WINDOWSTATIC_AUTOWRAPPED, "autowrapped", tabc);
			PrintBool(f, s & WINDOWSTATIC_POPUP, "popup", tabc);
			PrintBool(f, s & WINDOWSTATIC_OUTOFBOUNDSCLICK, "outOfBoundsClick", tabc);
			PrintBool(f, s & WINDOWSTATIC_LEGACYSPLITSCREENSCALE, "legacySplitScreenScale", tabc);
			PrintBool(f, s & WINDOWSTATIC_HIDDENDURINGFLASH, "hiddenDuringFlashbang", tabc);
			PrintBool(f, s & WINDOWSTATIC_HIDDENDURINGSCOPE, "hiddenDuringScope", tabc);
			PrintBool(f, s & WINDOWSTATIC_HIDDENDURINGUI, "hiddenDuringUI", tabc);
			PrintBool(f, s & WINDOWSTATIC_TEXTONLYFOCUS, "textOnlyFocus", tabc);
		}

		void PrintDynamicFlags(FILE *f, int d, int tabc)
		{
			PrintBool(f, d & WINDOWDYNAMIC_VISIBLE, "visible 1", tabc);
		}
    	
        void PrintWindow(FILE *f, game::windowDef_t *w, int tabc)
        {
            PrintString(f, w->name, "name", tabc);
            PrintRect(f, w->rect, "rect", tabc);
            PrintStaticFlags(f, w->staticFlags, tabc);
            PrintDynamicFlags(f, w->dynamicFlags[0], tabc);
            PrintString(f, w->group, "group", tabc);
            PrintInt(f, w->style, "style", tabc);
            PrintInt(f, w->border, "border", tabc);
            PrintFloat(f, w->borderSize, "bordersize", tabc);
            PrintInt(f, w->ownerDraw, "ownerdraw", tabc);
            PrintInt(f, w->ownerDrawFlags, "ownerdrawFlag", tabc);
            PrintColor(f, w->foreColor, "forecolor", tabc);
            PrintColor(f, w->backColor, "backcolor", tabc);
            PrintColor(f, w->borderColor, "bordercolor", tabc);
            PrintColor(f, w->outlineColor, "outlinecolor", tabc);
            PrintColor(f, w->disableColor, "disablecolor", tabc);
            if (w->background)
                PrintString(f, w->background->name, "background", tabc);
        }

    	void DumpItem(FILE *f, game::itemDef_s *i)
		{
			fputs("\t\titemDef\n\t\t{\n", f);

			PrintWindow(f, &i->window, 3);
			// type info
			PrintInt(f, i->type, "type", 3);
			PrintInt(f, i->alignment, "align", 3);
			PrintInt(f, i->fontEnum, "textfont", 3);
			PrintInt(f, i->textAlignMode, "textalign", 3);
			PrintFloat(f, i->textalignx, "textalignx", 3);
			PrintFloat(f, i->textaligny, "textaligny", 3);
			PrintFloat(f, i->textscale, "textscale", 3);
			PrintColor(f, i->glowColor, "glowColor", 3);
			PrintBool(f, i->decayActive, "decodeEffect", 3);
			if (i->type == ITEM_TYPE_GAME_MESSAGE_WINDOW)
			{
				PrintInt(f, i->gameMsgWindowIndex, "gamemsgwindowindex", 3);
				PrintInt(f, i->gameMsgWindowMode, "gamemsgwindowmode", 3);
			}
			PrintString(f, i->text, "text", 3);
			PrintBool(f, i->itemFlags & 1, "textsavegame", 3);
			PrintBool(f, i->itemFlags & 2, "textcinematicsubtitle", 3);
			PrintFloat(f, i->special, "feeder", 3);
			if (i->focusSound != nullptr) PrintString(f, i->focusSound->aliasName, "focusSound", 3);
			if (i->type != ITEM_TYPE_SLIDER && i->type != ITEM_TYPE_DVARENUM)
			{
				PrintString(f, i->dvar, "dvar", 3);
				PrintItemDefData(f, i->type, &i->typeData, 3);
			}
			else PrintItemDefData(f, i->type, &i->typeData, 3);
			PrintDvarTest(f, i->dvarTest, i->enableDvar, i->dvarFlags, 3);
			// expressions
			PrintItemFloatExpressions(f, i->floatExpressionCount, i->floatExpressions, 3);
			PrintStatement(f, i->visibleExp, "visible when", 3);
			PrintStatement(f, i->disabledExp, "disabled when", 3);
			PrintStatement(f, i->textExp, "exp text", 3);
			PrintStatement(f, i->materialExp, "exp material", 3);
			PrintItemKeyHandler(f, i->onKey, "execKeyInt", 3);
			// statements
			PrintMenuEventHandlerSet(f, i->mouseEnterText, "mouseEnterText", 3);
			PrintMenuEventHandlerSet(f, i->mouseExitText, "mouseExitText", 3);
			PrintMenuEventHandlerSet(f, i->mouseEnter, "mouseEnter", 3);
			PrintMenuEventHandlerSet(f, i->mouseExit, "mouseExit", 3);
			PrintMenuEventHandlerSet(f, i->action, "action", 3);
			PrintMenuEventHandlerSet(f, i->accept, "accept", 3);
			PrintMenuEventHandlerSet(f, i->onFocus, "onFocus", 3);
			PrintMenuEventHandlerSet(f, i->leaveFocus, "leaveFocus", 3);

			fputs("\t\t}\n", f);
		}
        
        void dumpMenus()
        {
            CreateDirectoryA(RAW_PATH, nullptr);
            CreateDirectoryA(MENUS_PATH, nullptr);

            game::DB_EnumXAssetEntries(game::ASSET_TYPE_MENU, [&](const game::XAssetEntry* entry)
            {
                console::debug("Dumping Menu: %s\n", entry->asset.header.menu->window.name);

                const char* fileName = utils::string::va("%s%s.menu", MENUS_PATH, entry->asset.header.menu->window.name);

                FILE* menuFile;
                fopen_s(&menuFile, fileName, "w");

                if (menuFile == nullptr)
                {
                    console::error("Failed to open menu file for %s", fileName);
                    return;
                }

                fputs("/*********************************************************\n", menuFile);
                fputs("***************** Dumped by IW4x64-Mod *******************\n", menuFile);
                fputs("*********************************************************/\n\n", menuFile);
                fputs("{\n\tmenuDef\n\t{\n", menuFile);
                fflush(menuFile);

                // menuDef
                PrintWindow(menuFile, &entry->asset.header.menu->window, 2);
                fflush(menuFile);

            	PrintColor(menuFile, entry->asset.header.menu->focusColor, "focuscolor", 2);
				PrintInt(menuFile, entry->asset.header.menu->fullScreen, "fullscreen", 2);
				PrintInt(menuFile, entry->asset.header.menu->fadeCycle, "fadeCycle", 2);
				PrintFloat(menuFile, entry->asset.header.menu->fadeClamp, "fadeClamp", 2);
				PrintFloat(menuFile, entry->asset.header.menu->fadeAmount, "fadeAmount", 2);
				PrintFloat(menuFile, entry->asset.header.menu->fadeInAmount, "fadeInAmount", 2);
				PrintFloat(menuFile, entry->asset.header.menu->blurRadius, "blurWorld", 2);
				PrintString(menuFile, entry->asset.header.menu->allowedBinding, "allowedBinding", 2);
				PrintString(menuFile, entry->asset.header.menu->soundName, "soundLoop", 2);
				PrintStatement(menuFile, entry->asset.header.menu->visibleExp, "visible when", 2);
				PrintStatement(menuFile, entry->asset.header.menu->rectXExp, "exp rect x", 2);
				PrintStatement(menuFile, entry->asset.header.menu->rectYExp, "exp rect y", 2);
				PrintStatement(menuFile, entry->asset.header.menu->rectHExp, "exp rect h", 2);
				PrintStatement(menuFile, entry->asset.header.menu->rectWExp, "exp rect w", 2);
				PrintStatement(menuFile, entry->asset.header.menu->openSoundExp, "exp openSound", 2);
				PrintStatement(menuFile, entry->asset.header.menu->closeSoundExp, "exp closeSound", 2);
				PrintItemKeyHandler(menuFile, entry->asset.header.menu->onKey, "execKeyInt", 2);
				PrintMenuEventHandlerSet(menuFile, entry->asset.header.menu->onOpen, "onOpen", 2);
				PrintMenuEventHandlerSet(menuFile, entry->asset.header.menu->onCloseRequest, "onRequestClose", 2);
				PrintMenuEventHandlerSet(menuFile, entry->asset.header.menu->onClose, "onClose", 2);
				PrintMenuEventHandlerSet(menuFile, entry->asset.header.menu->onESC, "onEsc", 2);

            	for (int i = 0; i < entry->asset.header.menu->itemCount; i++)
            	{
					DumpItem(menuFile, entry->asset.header.menu->items[i]);
					fflush(menuFile);
				}

				fputs("\t}\n}", menuFile);
				fclose(menuFile);
            }, true);
        }
    }
    
    class component final : public component_interface
    {
        public:
            void post_load() override
            {
                command::add("menuDump", [&]()
                {
                    dumpMenus();
                });              
            }
    };
}

REGISTER_COMPONENT(menus::component);