������� ��������:

��� ��� ��������� �� ������ ��������� ���������� ������� �� �������,
��� ������� ����������� �� ������������ ����������, ������� ����������
������� � ��� ����� �������� ������ �� ������������ � ������� � �������,
����������� ������������ ������� ��������� ��� ��������������, �� � �����
����������� �� ��������� �����:
��������� ������� �� ���� �������: Bus � Module, ��������� ������ Bus
�������� � ���� ������� ������ Module � ������������ � ������������� �����������.
��� �������� ������� Bus ���������� ������� ���������������� ����:
	Bus bus("config.ini");
����� ����� ������ ����� ��������� ������ � ������������ � ������� �������������,
� ���� �������������� ���������� std::unordered_map <�����_������, ������>. ��� ��������
����� ����������� ������ ������ ��� ������� �������� ���������� ����������� O(1).
������ ��� ������� ������ ��������� � ���� ����������� std::vector, ���������� � ����
���� ��� ��������� ���������. ��� �������� ��������� ������������ �������� ���������
������, �� �������� �� ������ �� �����, ��� ������� ���������, � �� �� ����� �������
����������� ���������� ���� ��������� �� ���.

������ ������� ������ ��� �������� ���������� ������:

	Module* module = bus.GetModuleByAddr(�����_������);
	if (module)
	{
		module->SetData(&������_�_�������);
	}

������ ������� ������ ��� �������� ���� ������� �����������:

	std::unordered_map <�����_������, ������_������_������ > V;
	for (auto it = V.begin(); it != V.end(); ++it)
	{
		Module* module = bus.GetModuleByAddr(V.first);
		module->SetData(&V.second);
	}

�������� ������ �� ���� ������������ ������� ������ SendData() ������ Bus. ������
������ ��������� � �� �� ����� ������� ��������� ���������� �����.

��� �� ������� �� ������� ������:

�� ���������� ������ ����������������� �����, ������������� ������������ "�������"
������ ������������ ������ Bus.

�� ������ ������ �������� ���������� �� ����������� � ����������� ���� ������ ����� � ������������
� ���������� �� �������.

�� ������� ��������� ������� �� ��-��������� �������� (�.�. ��������� �������� ��� �����-�� ������ ����� �� �����)
����������� ������� ��������� �������: ��������� ��� ����� ������ ���������� ��� ���, �� ���������� ���� ������ ����
�������. ����� ���� ��� �� ��� ����� ���� ������� �������� - ����������, ���������� ��������� ��� �������� �� Bus::SendData()
� ������������ ��� ������ ���������� � ������ �������� ��������, ��� �� ��� ����� ����, �������� ������, ������� ������,
��� ���������� ������� ������� ����� ��������.