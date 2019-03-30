#include "BehaviorScheduler.h"

namespace gameframework
{
	BehaviorScheduler::BehaviorScheduler()
	{

	}

	BehaviorScheduler::~BehaviorScheduler()
	{
	
	}

	void BehaviorScheduler::Update(Vertices* pVertices)
	{
		UpdateCanRunning();

		for (auto& behaviorData : m_nodeDatas)
		{
			if (!behaviorData.m_canRunning) continue;

			behaviorData.m_pT->Impart(pVertices);
		}
	}

	bool BehaviorScheduler::IsParentNodeEnded(NodeData& nodeData)
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
}
