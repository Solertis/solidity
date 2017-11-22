/*
	This file is part of solidity.

	solidity is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	solidity is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with solidity.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
 * Optimiser component that performs function inlining.
 */

#include <libjulia/optimiser/FunctionalInliner.h>

#include <libjulia/optimiser/InlinableFunctionFilter.h>

#include <libsolidity/inlineasm/AsmData.h>
#include <libsolidity/inlineasm/AsmScope.h>

#include <libevmasm/SemanticInformation.h>

#include <libsolidity/interface/Exceptions.h>

using namespace std;
using namespace dev;
using namespace dev::julia;
using namespace dev::solidity;
using namespace dev::solidity::assembly;



void FunctionalInliner::run()
{
	InlinableFunctionFilter filter;
	filter(*m_block);
	m_inlinableFunctions = filter.inlinableFunctions();

	(*this)(*m_block);
}

bool FunctionalInliner::operator()(FunctionalInstruction& _instr)
{
	bool pure = eth::SemanticInformation::movable(_instr);

	for (auto const& arg: _instr.arguments)
		if (!boost::apply_visitor(*this, arg))
			pure = false;
	return pure;
}

void FunctionalInliner::operator()(FunctionCall& _funCall)
{
	bool allArgsPure = true;

	for (auto const& arg: _funCall.arguments)
		if (!boost::apply_visitor(*this, arg))
			allArgsPure = false;

	if (allArgsPure)

	auto it = m_inlinableFunctions.find(_funCall.functionName.name);
	if (it != m_inlinableFunctions.end())
	{
		FunctionDefinition const&

	}

	// Pureness of this depends on the pureness of the replacement,
	// i.e. the pureness of the function itself.
	// Perhaps we can just re-run?

	// If two functions call each other, we have to exit after some iterations.

	return allArgsPure;
}

void FunctionalInliner::operator()(StackAssignment& _assignment);
void FunctionalInliner::operator()(Assignment& _assignment);
void FunctionalInliner::operator()(VariableDeclaration& _varDecl);
void FunctionalInliner::operator()(Switch& _switch);
void FunctionalInliner::operator()(FunctionDefinition&);
void FunctionalInliner::operator()(ForLoop&);
void FunctionalInliner::operator()(Block& _block);
