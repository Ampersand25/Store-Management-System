QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
		if (role == Qt::FontRole)
		{
			QFont font;
			font.setItalic(false);
			font.setBold(false);

			return font;
		}
		else if (role == Qt::BackgroundRole)
			return QBrush(Qt::white, Qt::SolidPattern);
		else if (role == Qt::DisplayRole)
		{
			if (orientation == Qt::Horizontal)
			{
				if (!section)
					return QString{ "Nume" };
				else if (section == 1)
					return QString{ "Tip" };
				else if (section == 2)
					return QString{ "Pret" };
				else if (section == 3)
					return QString{ "Producator" };
			}
			else if (orientation == Qt::Vertical)
				return QString{ "%1" }.arg(section + 1);
		}

		return QVariant{};
	}