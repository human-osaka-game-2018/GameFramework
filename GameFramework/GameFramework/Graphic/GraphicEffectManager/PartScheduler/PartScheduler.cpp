#include "PartScheduler.h"

namespace gameframework
{
	PartScheduler::PartScheduler()
	{

	}

	PartScheduler::~PartScheduler()
	{
	
	}

	void PartScheduler::Update()
	{
		UpdateCanRunning();

		for (auto& nodeData : m_nodeDatas)
		{
			if (IsPartEnd(nodeData)) continue;

			nodeData.m_pT->Update();
		}
	}

	void PartScheduler::Render(bool isAdditionBlendMode)
	{
		for (auto& nodeData : m_nodeDatas)
		{
			if (IsPartEnd(nodeData)) continue;

			nodeData.m_pT->Render(isAdditionBlendMode);
		}
	}

	bool PartScheduler::IsEnd()
	{
		for (auto& nodeData : m_nodeDatas)
		{
			//ノードが終了していないかつ動作時間がまだあるということは完全に終了はしていない
			if (!nodeData.m_pT->IsEnd() && nodeData.m_runableRemainingFrame != 0) return false;
		}

		return true;
	}

	bool PartScheduler::IsParentNodeEnded(NodeData& nodeData)
	{
		//親ノードが終了しているかチェック
		int index = nodeData.m_parentNodeIndex;

		//親ノードがある
		if (index != NodeData::DEFAULT_START)
		{
			//親ノードが終了していない
			if (!m_nodeDatas[index].m_pT->IsEnd() &&
				m_nodeDatas[index].m_runableRemainingFrame != 0) return false;
		}

		return true;
	}

	bool PartScheduler::IsPartEnd(const NodeData& nodeData)
	{
		if (!nodeData.m_canRunning || nodeData.m_pT->IsEnd()) return true;

		return false;
	}
}
